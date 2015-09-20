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
#include <regex>

#include <sys/stat.h>

#include "include/HttpRequest.h"
#include "include/ErrorCodes.h" 

using namespace webkit;

HttpResponse* HttpRequest::GetResponse(std::string buffer,
				       std::string documentRoot,
				       std::string documentIndex,
				       std::map<std::string,
				       std::string> mimes)
{
  HttpResponse* response;
  std::string errorMsg;
  ErrorCode errorCode = NONE;
  // If unable to parse, it's not GET method
  // return ErrorCode 404 Invalid method
  if ((errorCode = this->ParseRequest(buffer, documentIndex, errorMsg)) != NONE) {

    // Invalid method
    if (errorCode == INVALID_METHOD) {
      response = new HttpResponse(std::string("400 Bad Request: Invalid Method:" + errorMsg), "",
				  Error400InvalidMethod.size());
      response->WriteContent(Error400InvalidMethod);
      return response;
    }

    // Invalid url
    if (errorCode == INVALID_URL) {
      response = new HttpResponse(std::string("400 Bad Request: Invalid URL:" + errorMsg), "",
				  Error400InvalidUrl.size());
      response->WriteContent(Error400InvalidUrl);
      return response;
    }

    // Invalid HTTP version
    if (errorCode == INVALID_HTTP_VERSION) {
      response = new HttpResponse(std::string("400 Bad Request: Invalid HTTP-Version:" + errorMsg), "",
				  Error400InvalidHttpVersion.size());
      response->WriteContent(Error400InvalidHttpVersion);
      return response;
    }
    
    return nullptr;
  }

  // actual path  = Root + virtual path + query
  auto requestedFile = documentRoot + path + query;

  size_t dot = requestedFile.find_last_of(".");
  std::string ext = requestedFile.substr(dot + 1);
 
  if (mimes.find(ext) == mimes.end()) {
    // std::cout << "ext: " << ext << "query " << query << std::endl;
    std::string error = std::string("501 Not Implemented:") + path + query;
    response = new HttpResponse(error, "", Error501NotImpl.size());
    response->WriteContent(Error501NotImpl);
    return response;
  }
 
  if (!FileExists(requestedFile)) {
    std::cout << "File not found. " << requestedFile << std::endl;
    // File doesn't exists
    std::string error = std::string("404 Not Found:") + path + query;
    response = new HttpResponse(error, "", Error404NotFound.size());
    response->WriteContent(Error404NotFound);
    return response;
  }
  
  auto mime = mimes[ext];

  std::ifstream file(requestedFile);

  // unable to open file, spit out "Internal server error" to the client.
  if (!file.good()) {
    std::cout << "Error in reading file. File maybe corrupted or may not exists!" << requestedFile << "\n";
    std::string error = std::string("500 Internal Server Error: Cannot allocate memory");
    response = new HttpResponse(error, mime, Error500InternalError.size());
    response->WriteContent(Error500InternalError);
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

ErrorCode HttpRequest::ParseRequest(std::string request, std::string documentIndex, std::string& error)
{
  std::stringstream parse(request);
  std::string str;

  parse >> str;

  // Handle GET request
  if(str == "GET") {
    method = HttpMethod::GET;
    parse >> str;

    size_t pos = str.find("?");

    if (pos != std::string::npos) {
      path = str.substr(0, pos);
      query = str.substr(pos + 1);
    } else {
      path = str;
    }

    // render default webpage if the client didn't request for any page
    if (this->path == "/")
      query = documentIndex;

    parse >> str;

    auto newline = str.find("\\n");
    if (newline != std::string::npos)
      str = str.substr(0, newline);
    
    if (str != "HTTP/1.0" && str != "HTTP/1.1") {
      error = str;
      std::cout << "Invalid http version: " << str << std::endl;
      return INVALID_HTTP_VERSION;
    }

    // regular expression is possible post g++-4.9
    // g++-4.8 has limited supported for regex and is buggy!
#if __GNUC__ * 100 + __GNUC_MINOR__  >= 409
    auto url = "http://localhost:8097" + path + query;
    auto url_regex =
      std::regex(R"((https?:\/\/)([a-z]*:\d*)([\w])*(\/[\w\d]+[\.|a-z|\d|-]*)+)");

    if (!std::regex_match(url, url_regex)) {
      // Invalid url
      error = url;
      std::cout << "Invalid url: " << url << std::endl;
      return INVALID_URL;
    }
#endif

  } else {
    error = str;
    std::cout << "Unknown request! Http method is not GET"  << "\n";
    std::cout << "Request dump:" << request << std::endl;
    return INVALID_METHOD;
  }
  
  return NONE;
}
