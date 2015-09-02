#include "http_header.cc"

using namespace webserver;

void http_header::set_header(string key, string value) {
  
}

http_header::http_header(string rescode, string content_type) {
  this->response = rescode;
  this->content_type = content_type;
}
