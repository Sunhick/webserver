#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <string>
#include <map>

using namespace std;

namespace SimpleWebServer {
  class WebServer {
  private:
    int listenPort = 5555; //default port
    string documentRoot = ""; // Document root directory
    string documentIndex = ""; // default page
    map<string, string> contentTypes; // dictionary of all content types
    
  public:
    WebServer(string cfile);
    bool Start();    // Start the web server
    bool Stop();    // Stop the web server. Graceful shutdown.
    bool Abort();    // Abort the server. Non-graceful shutdown
  };
}

#endif
