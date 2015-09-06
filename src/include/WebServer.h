/****************************************************
 *  Header for http web server
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#ifndef WEB_KIT_WEB_SERVER_H
#define WEB_KIT_WEB_SERVER_H

#include <string>
#include <map>

#define BACKLOG 32

namespace webkit {
  class WebServer {
  private:
    int sockfd; 			// socket file descriptor
    int listenPort = 5555; 		//default port
    std::string documentRoot = ""; 		// Document root directory
    std::string documentIndex = ""; 		// default page
    std::map<std::string, std::string> contentTypes; 	// dictionary of all content types

    // open the server socket for incoming connections
    int OpenSocket(int backlog);
    // Print the message and exit the program
    int Die(const char *format, ...);
    // Handle client request in separate thread
    void HandleRequest(int new_fd);
    
  public:
    WebServer(std::string cfile);
    bool Start();    			// Start the web server
    void Stop();    			// Stop the web server. Graceful shutdown.
    void Abort();    			// Abort the server. Non-graceful shutdown
  };
}

#endif
