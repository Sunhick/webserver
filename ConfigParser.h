#ifndef WEB_SERVER_CONFIG_PARSER_H
#define WEB_SERVER_CONFIG_PARSER_H

#include <map>
#include <vector>
#include <string>

using namespace std;

namespace SimpleWebServer {
  class ConfigParser {
  private:
    map<string, string> parsedValues;
    vector<string> Split(const string& str,
			 int delimiter(int) = ::isspace);

      public:
    ConfigParser(string configfile);
    string GetString(string key);
    int GetInteger(string key);
  };
}

#endif
