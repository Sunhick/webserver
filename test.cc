#include <iostream>
#include "ConfigParser.h"

using namespace std;
using namespace WebServer;

int main(int argc, char *argv[])
{
  ConfigParser c("ws.conf");
  auto root = c.GetString("DocumentRoot");
  cout << "Document root: " << root << endl;

  auto port = c.GetInteger("Listen");
  cout << "Port : " << port << endl;

  auto index = c.GetString("DirectoryIndex");
  cout << "Index file: " << index  << "\n";

  auto html = c.GetString(".html");
  cout << "html: " << html  << "\n";

  auto png = c.GetString(".png");
  cout << "png: " << png  << "\n";
  
  
  return 0;
}
