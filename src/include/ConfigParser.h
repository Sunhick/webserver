/****************************************************
 *  Header file for web configuration parser
 *
 * Author : Sunil bn <sunhick@gmail.com>
 *****************************************************/
#ifndef WEB_KIT_CONFIG_PARSER_H
#define WEB_KIT_CONFIG_PARSER_H

#include <map>
#include <vector>
#include <string>

using namespace std;

namespace webkit {
  // Configuration file parser(ws.conf)
  class ConfigParser {
  private:
    map<string, string> parsedValues;
    // Tokenize the given string based to delimiter
    vector<string> Split(const string& str, int delimiter(int) = ::isspace);

  public:
    ConfigParser(string configfile);
    ~ConfigParser();
    // Get value corresponding to key as string 
    string GetString(string key);
    // Get value corresponding to key as integer
    int GetInteger(string key);
  };
}

#endif
