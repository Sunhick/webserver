/****************************************************
 *  Http web server implmentation
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include <exception>
#include <csignal>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <ctime>

#include "include/Common.h"
#include "include/WebServer.h"
#include "include/ConfigParser.h"
#include "include/HttpRequest.h"

using namespace webkit;

int gSockId;

WebServer::WebServer(std::string conf)
{
  ConfigParser config(conf);
  this->listenPort = config.GetInteger("Listen");
  this->documentRoot = config.GetString("DocumentRoot");
  this->documentIndex = config.GetString("DirectoryIndex");

  // Content types
  this->contentTypes.insert(std::pair<std::string, std::string>("html", config.GetString(".html")));
  this->contentTypes.insert(std::pair<std::string, std::string>("html", config.GetString(".htm")));
  this->contentTypes.insert(std::pair<std::string, std::string>("txt", config.GetString(".txt")));
  this->contentTypes.insert(std::pair<std::string, std::string>("png", config.GetString(".png")));
  this->contentTypes.insert(std::pair<std::string, std::string>("gif", config.GetString(".gif")));
  this->contentTypes.insert(std::pair<std::string, std::string>("jpg", config.GetString(".jpg")));
  this->contentTypes.insert(std::pair<std::string, std::string>("css", config.GetString(".css")));
  this->contentTypes.insert(std::pair<std::string, std::string>("js", config.GetString(".js")));
  this->contentTypes.insert(std::pair<std::string, std::string>("ico", config.GetString(".ico")));
}

int WebServer::OpenSocket(int backlog)
{
  struct sockaddr_in sin; 	// an Internet endpoint address 
  int sockfd;               	// socket descriptor 

  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;

#ifdef USE_IP
  // support for connecting from different host
  sin.sin_addr.s_addr = inet_addr("192.168.0.16");
#else
  // use local host
  sin.sin_addr.s_addr = INADDR_ANY;
#endif

  // Map port number (char string) to port number (int)
  if ((sin.sin_port=htons((unsigned short)this->listenPort)) == 0)
    Die("can't get \"%sockfd\" port number\n", this->listenPort);

  // Allocate a socket
  sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockfd < 0)
    Die("can't create socket: %sockfd\n", strerror(errno));

  // Bind the socket
  if (bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
    fprintf(stderr, "can't bind to %d port: %s; Trying other port\n",
	    this->listenPort, strerror(errno));
    sin.sin_port=htons(0); /* request a port number to be allocated
			      by bind */
    if (bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
      Die("can't bind: %sockfd\n", strerror(errno));
    } else {
      int socklen = sizeof(sin);
      if (getsockname(sockfd, (struct sockaddr *)&sin, (socklen_t *)&socklen) < 0)
	Die("getsockname: %sockfd\n", strerror(errno));
      printf("New server port number is %d\n", ntohs(sin.sin_port));
    }
  }

  if (listen(sockfd, backlog) < 0)
    Die("can't listen on %sockfd port: %sockfd\n", this->listenPort, strerror(errno));

  return sockfd;
}

int WebServer::Die(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  exit(EXIT_FAILURE);  
}

bool WebServer::Start()
{
  try {
    
    // open master socket for client to connect
    // a maximum of 32 client can connect simultaneously.
    gSockId = sockfd = OpenSocket(BACKLOG);

    // unable to open socket.
    if (sockfd < 0)
      return false;

    // Install a signal handler for graceful shut of server
    std::signal(SIGINT, [](int signal) {
	std::cout << "\nSignal caught!" << "Closing server socket..." << std::endl;
	close(gSockId);
	exit(EXIT_FAILURE);
      });
    
    vector<thread> requests; // request threads

    // Accept incoming connections & launch
    // the request thread to service the clients
    while (true) {
      struct sockaddr_in their_addr;
      socklen_t sin_size = sizeof(struct sockaddr_in);
      int newfd;
      if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
	perror("accept");
	continue;
      }

      // fork vs thread ?
      // Fork : overhead of creating process
      // thread : lightweight process and faster in setting up
      // provide service to client in a different thread
      requests.push_back(thread(&WebServer::DispatchRequest,this, newfd));
    
      std::cout << "Accepted the client! Client Count:" << requests.size() << std::endl;
    }

    // Make sure all clients are serviced, before server goes down
    for (auto &thread : requests)
      thread.join();
    
  } catch (std::exception& e) {
    std::cout << "Error in server(main) thread! Reason: " << e.what() << std::endl;
  } catch (...) {
    std::cout << "Error in server(main) thread!" << std::endl;
  }

  return true;
}

void WebServer::DispatchRequest(int newfd)
{
  try {

    std::cout << "Worker thread(client) socket Id: " << newfd << std::endl;

    // Make read() call non-blocking.
    int flags = fcntl(newfd, F_GETFL, 0);
    fcntl(newfd, F_SETFL, flags | O_NONBLOCK);
    
    // Persistant-connection(pipeline):
    // Keep the socket open for 10s for incoming connections.
    // after time out the socket will be closed.
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>::zero();
    bool keepAlive = true; // initially set to true. then update per the request
    
    while(elapsed_seconds.count() < TIME_OUT && keepAlive)  {
      // while (timer is running) {
      //    serve_client();
      // }   
      char buff[4096];
      elapsed_seconds = std::chrono::system_clock::now() - start;
      
      if (read(newfd, buff, 4096) == -1) {
	// std::cout << "Error in reading the request" << std::endl;
	// return;
	continue;
      }

      // process the buffer if it contains request
      if (buff == NULL || strlen(buff) == 0) continue;

      // std::cout << "Buffer size : " << strlen(buff) << std::endl;
      // std::cout << "Thread id:" << std::this_thread::get_id()  << "\nBuffer: " << buff  << "\n";
      // std::cout << reqlines << std::endl;

      std::string reqlines = std::string(buff);
      std::size_t current = 0;
      std::size_t next = std::string::npos;

      do {
	// process all requests from the client.
	// for eg: Client may send multiple requests in shot.

	//split based on double new line 
	next = reqlines.find("\\n\\n", current);
	auto reqline = std::string("");
	if (next != std::string::npos) {
	  reqline = reqlines.substr(current, next - current);
	  current = next + 4;
	} else {
	  reqline = reqlines;
	}

	// parse the client request and respond
	HttpRequest request;
	auto response = request.GetResponse(reqline,
					    this->documentRoot,
					    this->documentIndex,
					    this->contentTypes,
					    keepAlive);
	
	if (response == nullptr)
	  continue;

	auto header  = response->GetHeader();
	write(newfd, header.c_str(), header.size());

	auto body = response->GetContent();
	// write body/content if available.
	if (!body.empty())
	  write(newfd, body.c_str(), body.size());

	delete response;
      } while (next != std::string::npos); // handle all multiple request line sent in one shot
      
      // Incoming request, reset the timer
      start = std::chrono::system_clock::now();
      elapsed_seconds = std::chrono::duration<double>::zero();

    } // while (timeout)

    std::cout << "Client request timeout! closing the socket... id: " << newfd << std::endl;
    close(newfd);
  } catch (std::exception& e) {
    std::cout << "Error occured in client(worker) thread! Reason: " << e.what()  << "\n";
  } catch (...) {
    std::cout << "Error occured in client(worker) thread!" << std::endl;
  }
}

void WebServer::Stop()
{
  close(sockfd);
}

void WebServer::Abort()
{
  Stop();
  abort();
}
