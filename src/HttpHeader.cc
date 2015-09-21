/****************************************************
 *  Header for http header
 *
 * Author : Sunil bn <sunhick@gmail.com>
 *****************************************************/
#include "include/HttpHeader.h"

using namespace webkit;

void HttpHeader::SetHeader(string key, string value)
{
  
}

HttpHeader::HttpHeader(string rescode, string content_type)
{
  this->response = rescode;
  this->content_type = content_type;
}
