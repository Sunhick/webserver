#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>

#include "ConfigParser.h"

using namespace WebServer;
using namespace std;

string ConfigParser::GetString(string key)
{
  if(!parsedValues.count(key)) {
    throw "Invalid key!";
  }

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
    /*
      istringstream buf(str);
      istream_iterator<std::string> beg(buf), end;

      vector<std::string> tokens(beg, end);
      parsedValues.insert(tokens.at(0), tokens.at(1));
    */
    vector<string> tokens = Split(str);
    parsedValues.insert(pair<string,string>(tokens.at(0), tokens.at(1)));
  }
}

vector<string> ConfigParser::Split(const string& str,
		     int delimiter(int))
{
  vector<string> result;
  auto e=str.end();
  auto i=str.begin();
  while(i!=e){
    i=find_if_not(i,e, delimiter);
    if(i==e) break;
    auto j=find_if(i,e, delimiter);
    result.push_back(string(i,j));
    i=j;
  }
  return result;
}
