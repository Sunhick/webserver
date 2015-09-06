#include <iostream>
#include <thread>

#include "include/ConfigParser.h"
#include "include/WebServer.h"

using namespace std;
using namespace webkit;

void launch_server();

int main(int argc, char *argv[])
{
  //launch the server thread and wait for it to halt.
  thread serverThread(launch_server);
  serverThread.join();

  return 0;
}

void launch_server()
{
  WebServer ws("ws.conf");
  ws.Start();
  ws.Stop();
}
