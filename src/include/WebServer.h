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

using namespace std;

namespace webkit {
  class WebServer {
  private:
    int sockfd; 			// socket file descriptor
    int listenPort = 5555; 		//default port
    string documentRoot = ""; 		// Document root directory
    string documentIndex = ""; 		// default page
    map<string, string> contentTypes; 	// dictionary of all content types

    // open the server socket for incoming connections
    int OpenSocket(int backlog);
    // Print the message and exit the program
    int Die(const char *format, ...);
    
  public:
    WebServer(string cfile);
    bool Start();    			// Start the web server
    bool Stop();    			// Stop the web server. Graceful shutdown.
    bool Abort();    			// Abort the server. Non-graceful shutdown
  };
}

#endif
