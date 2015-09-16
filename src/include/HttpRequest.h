/****************************************************
 *  Header file for http request
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#ifndef WEB_KIT_HTTP_REQUEST_H
#define WEB_KIT_HTTP_REQUEST_H

#include <string>

#include "HttpResponse.h"

namespace webkit {

  enum HttpMethod {
    GET,
    POST,
    DELETE,
    HEAD,
    PUT,
    TRACE,
    CONNECT
  };
  
  class HttpRequest {
  private:
    std::string path;
    std::string query;
    HttpMethod method;

    bool ParseRequest(char* request);
    bool FileExists(const std::string& name);
  public:
    HttpResponse* GetResponse(char* buffer, std::string documentRoot,
			      std::string documentIndex, std::map<std::string, std::string> mimes);
  };
}

#endif
