#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <string>
#include <map>

#define BACKLOG 32

using namespace std;

namespace SimpleWebServer {
  class WebServer {
  private:
    int sockfd; // socket file descriptor
    int listenPort = 5555; //default port
    string documentRoot = ""; // Document root directory
    string documentIndex = ""; // default page
    map<string, string> contentTypes; // dictionary of all content types

    int OpenServerSocket(int backlog);
    int Die(const char *format, ...);
    
  public:
    WebServer(string cfile);
    bool Start();    // Start the web server
    bool Stop();    // Stop the web server. Graceful shutdown.
    bool Abort();    // Abort the server. Non-graceful shutdown
  };
}

#endif
