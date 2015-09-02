#include "WebServer.h"
#include "ConfigParser.h"

using namespace SimpleWebServer;

WebServer::WebServer(string conf)
{
  ConfigParser c(conf);
  this->listenPort = c.GetInteger("Listen");
  this->documentRoot = c.GetString("DocumentRoot");
  this->documentIndex = c.GetString("DirectoryIndex");
  // Content types
  this->contentTypes.insert(pair<string, string>(".html", c.GetString(".html")));
  this->contentTypes.insert(pair<string, string>(".txt", c.GetString(".txt")));
  this->contentTypes.insert(pair<string, string>(".png", c.GetString(".png")));
  this->contentTypes.insert(pair<string, string>(".gif", c.GetString(".gif")));
}

bool WebServer::Start()
{
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
