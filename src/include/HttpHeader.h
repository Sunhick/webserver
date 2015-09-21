/****************************************************
 *  Header for http header
 *
 * Author : Sunil bn <sunhick@gmail.com>
 *****************************************************/
#ifndef WEB_KIT_HTTP_HEADER_H
#define WEB_KIT_HTTP_HEADER_H

#include <string>
#include <unordered_map>

using namespace std;

namespace webkit {
  // http header format
  class HttpHeader {
  private:
    unordered_map<string, string> headers;
    string response;
    string content_type;
  public:
    HttpHeader(string rescode, string content_type);
    void SetHeader(string key, string value);
  };
}

#endif
