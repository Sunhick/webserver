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

#include <sys/stat.h>

#include "include/HttpRequest.h"
#include "include/ErrorCodes.h" 

using namespace webkit;

HttpResponse* HttpRequest::GetResponse(char* buffer, std::string documentRoot, std::string documentIndex,
				       std::map<std::string, std::string> mimes)
{

  HttpResponse* response;
  
  // If unable to parse, it's not GET method
  // return ErrorCode 404 Invalid method
  if (!this->ParseRequest(buffer)) {
    /* response = new HttpResponse("400 Bad Request: Invalid Method", "",
				Error400InvalidMethod.size());
    response->WriteContent(Error400InvalidMethod);
    return response; */
    return nullptr;
  }

  // render default webpage if the client didn't request for any page
  if (this->path == "/")
    query = documentIndex;	

  // actual path  = Root + virtual path + query
  auto requestedFile = documentRoot + path + query;

  /* if (!FileExists(requestedFile)) {
    std::cout << "File not found. " << requestedFile << std::endl;
    // File doesn't exists
    std::string error = std::string("404 Not Found:") + path + query;
    response = new HttpResponse(error, "", Error404NotFound.size());
    response->WriteContent(Error404NotFound);
    return response;
    }*/

  size_t dot = query.find_last_of(".");
  std::string ext = query.substr(dot + 1);

  /*
  if (mimes.find(ext) == mimes.end()) {
    std::string error = std::string("501 Not Implemented:") + path + query;
    response = new HttpResponse(error, "", Error404NotFound.size());
    response->WriteContent(Error404NotFound);
    return response;
  }
  */

  auto mime = mimes[ext];

  std::ifstream file(requestedFile);
  if (!file.good()) {
    std::cout << "Error in reading file. File maybe corrupted or may not exists!" << requestedFile << "\n";
    std::string error = std::string("404 Not Found:") + path + query;
    response = new HttpResponse(error, mime, Error404NotFound.size());
    response->WriteContent(Error404NotFound);
    return response;
  }

  file.seekg(0, std::ios_base::end);
  size_t size = file.tellg();
  file.seekg(0);

  std::string responseCode = "200 OK";
  response= new HttpResponse(responseCode, mime, size);
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

bool HttpRequest::FileExists(const std::string& name)
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

bool HttpRequest::ParseRequest(char* request)
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
    std::cout << "Unknown request! Http method is not GET"  << "\n";
    std::cout << "Request dump:" << request << std::endl;
    // throw "Unknown request";
    return false;
  }
  return true;
}
