#ifndef WEB_SERVER_HTTP_HEADER_H
#ifndef WEB_SERVER_HTTP_HEADER_H

#include <string>
#include <unordered_map>

using namespace std;

namespace webserver {
  // http header format
  class http_header {
  private:
    unordered_map<string, string> headers;
    string response;
    string content_type;
  public:
    http_header(string rescode, string content_type);
    void set_header(string key, string value);
  };
}

#nendif
