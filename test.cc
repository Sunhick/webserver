#include <iostream>

#include "ConfigParser.h"
#include "WebServer.h"

using namespace std;
using namespace SimpleWebServer;

int main(int argc, char *argv[])
{
  WebServer ws("ws.conf");
  ws.Start();
  return 0;
}
