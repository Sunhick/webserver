#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "WebServer.h"
#include "ConfigParser.h"

using namespace std;
using namespace SimpleWebServer;

WebServer::WebServer(string conf)
{
  ConfigParser c(conf);
  this->listenPort = c.GetInteger("Listen");
  this->documentRoot = c.GetString("DocumentRoot");
  this->documentIndex = c.GetString("DirectoryIndex");
  // Content types
  this->contentTypes.insert(pair<string, string>("html", c.GetString(".html")));
  this->contentTypes.insert(pair<string, string>("txt", c.GetString(".txt")));
  this->contentTypes.insert(pair<string, string>("png", c.GetString(".png")));
  this->contentTypes.insert(pair<string, string>("gif", c.GetString(".gif")));
}

int WebServer::OpenServerSocket(int backlog)
{
  struct sockaddr_in sin; /* an Internet endpoint address  */
  int sockfd;              /* socket descriptor */

  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;

  /* Map port number (char string) to port number (int) */
  if ((sin.sin_port=htons((unsigned short)this->listenPort)) == 0)
    Die("can't get \"%sockfd\" port number\n", this->listenPort);

  /* Allocate a socket */
  sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockfd < 0)
    Die("can't create socket: %sockfd\n", strerror(errno));

  /* Bind the socket */
  if (bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
    fprintf(stderr, "can't bind to %sockfd port: %sockfd; Trying other port\n",
	    this->listenPort, strerror(errno));
    sin.sin_port=htons(0); /* request a port number to be allocated
			      by bind */
    if (bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
      Die("can't bind: %sockfd\n", strerror(errno));
    else {
      int socklen = sizeof(sin);
      int x = getsockname(sockfd, (struct sockaddr *)&sin, (socklen_t *)&socklen);
      if (x < 0)
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
  exit(1);
}

bool WebServer::Start()
{
  // open master socket for client to connect
  // a maximum of 32 client can connect simultaneously
  sockfd = OpenServerSocket(BACKLOG);

  // keep listening for incoming connections
  while(true) {
    struct sockaddr_in their_addr;
    socklen_t sin_size = sizeof(struct sockaddr_in);
    int new_fd;
    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
      perror("accept");
      continue;
    }

    char buf[4096];
    if(read(new_fd, buf, 4096) == -1) {
      cout << "Error in reading the request" << endl;
      continue;
    }

    cout << "Contents" << endl << buf << endl;
    
    cout << "Accepted the client!" << endl;
  }

  // todo: start the server
  return true;
}

bool WebServer::Stop()
{
  // todo: gracefull shutdown
  return false;
}

bool WebServer::Abort()
{
  // todo: abort the server
  return false;
}
