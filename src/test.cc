/****************************************************
 *  Main file for http web server
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#include <iostream>
#include <exception>

#include "include/ConfigParser.h"
#include "include/WebServer.h"

void LaunchServer();

int main(int argc, char *argv[])
{
  LaunchServer();
  return 0;
}

void LaunchServer()
{
  webkit::WebServer httpd("ws.conf");

  try {
    auto socketOpened = httpd.Start();

    if (socketOpened)
      httpd.Stop();
    
  } catch (std::exception& e) {
    std::cout << "Server faulted! Reason:" << e.what()  << "\n";
  }

}
