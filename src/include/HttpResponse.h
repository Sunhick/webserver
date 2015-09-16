/****************************************************
 *  Header file  for http response
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#ifndef WEB_KIT_HTTP_RESPONSE_H
#define WEB_KIT_HTTP_RESPONSE_H

#include <string>
#include <sstream>

#define SERVER_NAME "WebkitServer" " " "1.0"

namespace webkit {
  class HttpResponse {
  private:
    std::stringstream header;
    std::string body;

  public:
    HttpResponse(const std::string& responseCode, const std::string& contentType, size_t bodySize);
    std::string GetHeader();
    std::string GetContent();
    void WriteContent(std::string data);
  };
}

#endif
