/****************************************************
 *  Http response file
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#include "include/HttpResponse.h"

using namespace webkit;

std::string HttpResponse::GetHeader()
{
  return header.str();
}

HttpResponse::HttpResponse(std::string& responseCode,
			   std::string& contentType,
			   size_t bodySize)
{
  header << "HTTP/1.0 " << responseCode << "\r\n";
  header << "Server: " SERVER_NAME "\r\n";
  header << "Content-Type: " << contentType << "\r\n";
  header << "Content-Length: " << bodySize << "\r\n";
  header << "\r\n";
}

void HttpResponse::WriteContent(std::string data)
{
  this->body.append(data);
}

std::string HttpResponse::GetContent()
{
  return this->body;
}
