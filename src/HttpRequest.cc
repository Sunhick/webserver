/****************************************************
 *  Http request file
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#include <stdexcept>
#include <sstream>
#include <map>
#include <fstream>
#include <iostream>

#include "include/HttpRequest.h"

using namespace webkit;

HttpResponse* HttpRequest::GetResponse(char* buffer, std::string documentRoot, std::string documentIndex,
				      std::map<std::string, std::string> mimes)
{
  this->ParseRequest(buffer);

  if (this->path == "/")
    query = documentIndex;	// render default webpage if the client didn't request for any page

  size_t dot = query.find_last_of(".");
  std::string ext = query.substr(dot + 1);
  auto mime = mimes[ext];

  auto requestedFile = /*documentRoot*/ std::string("/home/sunny/wrk/netsys/webserver/www") + path + query;
  std::ifstream file(requestedFile);
  if (!file.good()) {
    std::cout << "Error in reading file." << requestedFile << "\n";
    // error in reading file
    //throw "error in reading file";
    return nullptr;
  }

  file.seekg(0, std::ios_base::end);
  size_t size = file.tellg();
  file.seekg(0);

  std::string responseCode = "200 OK";
  HttpResponse* response= new HttpResponse(responseCode, mime, size);
  const size_t blockSize = 4096;
  std::streampos pos = 0;
  std::string data;

  // write the actual file content
  while ((pos = file.tellg()) >= 0 && (size_t)pos < size - 1){ 
    data.resize(size - (size_t)pos < blockSize ? size - (size_t)pos : blockSize);
    file.read(&data[0], data.size());
    response->WriteContent(data);
  }

  file.close();
  return response;
}

void HttpRequest::ParseRequest(char* request)
{
  std::stringstream parse(request);
  std::string str;

  parse >> str;

  // Handle GET request
  if(str == "GET"){
    method = HttpMethod::GET;
    parse >> str;

    size_t pos = str.find("?");

    if (pos != std::string::npos) {
      path = str.substr(0, pos);
      query = str.substr(pos + 1);
    }

    else path = str;
  } else {
    throw "Unknown request";
  }
}
