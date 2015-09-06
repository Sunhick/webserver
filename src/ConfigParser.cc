/****************************************************
 *  Parses web configuration file
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>

#include "include/ConfigParser.h"

using namespace webkit;

std::string ConfigParser::GetString(std::string key)
{
  if (!parsedValues.count(key))
    throw "Invalid key!";

  return parsedValues[key];
}

int ConfigParser::GetInteger(std::string key)
{
  if (!parsedValues.count(key))
    throw "Invalid key";
  
  auto value = parsedValues[key];
  return atoi(value.c_str());
}

ConfigParser::~ConfigParser()
{
  // clean up the parsed variables
  this->parsedValues.clear();
}

ConfigParser::ConfigParser(std::string configfile)
{
  ifstream cfile(configfile.c_str());
  if (!cfile.good())
    throw "File doesn't exists!";

  for (std::string str; getline(cfile, str);) {
    if (str[0] == '#') // comment line, skip it.
      continue;

    auto tokens = Split(str);
    parsedValues.insert(std::pair<std::string, std::string>(tokens.at(0), tokens.at(1)));
  }
}

std::vector<std::string> ConfigParser::Split(const std::string& str, int delimiter(int))
{
  std::vector<std::string> result;
  auto end = str.end();
  auto start = str.begin();
  while (start != end) {
    start = find_if_not(start, end, delimiter);
    if (start == end) break;
    auto j = find_if(start, end, delimiter);
    result.push_back(string(start,j));
    start = j;
  }

  return result;
}
