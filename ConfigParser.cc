#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>

#include "ConfigParser.h"

using namespace WebServer;
using namespace std;

string ConfigParser::GetString(string key)
{
  if(!parsedValues.count(key))
    throw "Invalid key!";

  return parsedValues[key];
}

int ConfigParser::GetInteger(string key)
{
  if(!parsedValues.count(key))
    throw "Invalid key";
  string value = parsedValues[key];
  return atoi(value.c_str());
}

ConfigParser::ConfigParser(string configfile)
{
  ifstream cfile(configfile.c_str());
  if(!cfile.good())
    throw "File doesn't exists!";

  for(string str; getline(cfile, str);) {
    if(str[0] == '#') // comment line, skip it.
      continue;

    vector<string> tokens = Split(str);
    parsedValues.insert(pair<string,string>(tokens.at(0), tokens.at(1)));
  }
}

vector<string> ConfigParser::Split(const string& str,
				   int delimiter(int))
{
  vector<string> result;
  auto end = str.end();
  auto start = str.begin();
  while(start != end){
    start = find_if_not(start,end,delimiter);
    if(start == end) break;
    auto j= find_if(start,end,delimiter);
    result.push_back(string(start,j));
    start =j;
  }
  return result;
}
