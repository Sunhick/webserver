/****************************************************
 *  List of Http error codes
 *
 * Author : Sunil bn <suba5417@colorado.edu>
 *****************************************************/
#ifndef WEB_KIT_ERROR_CODES_H
#define WEB_KIT_ERROR_CODES_H

#include <string>

#define NONE			 -1
#define INVALID_METHOD		 9400
#define INVALID_URL		 9401
#define INVALID_HTTP_VERSION	 9402
#define NOT_FOUND		 9404
#define NOT_IMPL		 9501
#define INTERNAL_ERROR		 9500


std::string Error400InvalidMethod = 
  R"(
<html>
	<body><b>400 Bad Request: Invalid Method</b></body>
</html>
)";

std::string Error400InvalidUrl =
  R"(
<html>
	<body><b>400 Bad Request: Invalid URL</b></body>
</html>
)";

std::string Error400InvalidHttpVersion = 
  R"(
<html>
	<body><b>400 Bad Request: Invalid HTTP Version</b></body>
</html>
)";

std::string Error404NotFound = 
  R"(
<html>
	<body><b>404 File not found!</b></body>
</html>
)";

std::string Error501NotImpl = 
  R"(
<html>
	<body><b>501 Not Implemented</b></body>
</html>
)";

std::string Error500InternalError =
  R"(
<html>
	<body><b>500 Internal Server Error: Cannot allocate memory</b></body>
</html>
)";
#endif
