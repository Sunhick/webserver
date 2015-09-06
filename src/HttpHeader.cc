/****************************************************
 *  Header for http header
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#include "include/HttpHeader.h"

using namespace webkit;

void http_header::SetHeader(string key, string value)
{
  
}

HttpHeader::HttpHeader(string rescode, string content_type)
{
  this->response = rescode;
  this->content_type = content_type;
}
