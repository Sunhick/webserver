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

  typedef int ErrorCode;
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

    ErrorCode ParseRequest(std::string request,
			   std::string documentIndex,
			   std::string& reqType,
			   bool& keepAlive);
    bool FileExists(const std::string& name);
  public:
    HttpResponse* GetResponse(std::string buffer,
			      std::string documentRoot,
			      std::string documentIndex,
			      std::map<std::string,
			      std::string> mimes,
			      bool& keepAlive);
  };
}

#endif
