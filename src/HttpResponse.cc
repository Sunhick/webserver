/****************************************************
 *  Http response file
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#include "include/HttpResponse.h"
#include "include/Common.h"

using namespace webkit;

std::string HttpResponse::GetHeader()
{
  return header.str();
}

HttpResponse::HttpResponse(const std::string& responseCode,
			   const std::string& contentType,
			   size_t bodySize)
{
  header << "HTTP/1.0 " << responseCode << "\r\n";
  header << "Server: " SERVER_NAME "\r\n";
  header << "Connection: " << "Keep-Alive" << "\r\n";
  header << "Keep-Alive: " << TIME_OUT << "\r\n";
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
