# =====================================================
# 
# 	Web server implementation in c++
# 
# =====================================================
# 					Sept 20, 2015


Contents:
==========
1. Introduction
2. Requirements
3. Compiling
4. Configuration
5. Web server deployment
6. Release
7. Bibliography
8. Bugs


1. Introduction:
=================

A web server is a computer system that processes requests via
HTTP, the basic network protocol used to distribute information
on the World Wide Web. The term can refer either to the entire
system, or specifically to the software that accepts and
supervises the HTTP requests.

  1.1 Source code:

  All source code files in the web server adheres to C++11
  stardards and has to be compiled with -std=c++11 or
  -std=c++xx flags.

   * ConfigParser.cc:  Parses the web server configuration file 
     (ws.conf) and creats a map of key-value pairs. "ws.conf"
     has to be in the same directory as that of the executable.

   * WebServer.cc: This is the heart of the web server. It opens
     the server socket, listen and accepts the incoming client
     requests forever untill shut. It spawns the worker thread
     for serving the accepted clients.

   * HttpRequest.cc: Parses the buffer containing the client
     request and prepares a http response. Apart from handling
     the request and response it also handles the errors/ fault
     from the client. Eg: web server handles error codes like
     400, 404, 500 & 501

   * HttpResponse.cc: This object holds the response to the client
     request. It is responsible for formatting the header(s) and
     body of the HTTP response.

   * HttpHeader.cc: Represents the HTTP request or response header.

   * main.cc: This file is the entry point to the web server and
     starts as a daemon process.
     

  1.2 Features:

    * Handling Multiple	Connections
    * Persistant connection (pipelining)
    * Error handling
    * Supports web configuration file


2. Requirements:
=================

To build the above code, GNU g++-4.8 or above is required. However
since i use c++11 features in the source code, It's recommended to
use GNU g++-4.9 tool chain for building the code.


3. Compiling:
===============

 3.1 Unzip the tar ball using the command,

	$ tar -xvzf suba5417.tar.gz

 3.2 Now issuse the build command using GNU make

	$ make all

 3.3 Run the web server as 

	$ ./httpd


4. Configuration: 
===================

As mentioned earlier, Web server should store all the configurations in
a ws.conf file. This file should be available in the same location as
that of executable (httpd). Contents of ws.conf

 #service port number
 Listen	8004

 #document root
 DocumentRoot "/home/sha2/www"

 #default web page
 DirectoryIndex  index.html index.htm index.ws

 #Content-Type which the server handles
 .html text/html
 .txt  text/plain
 .png  image/png
 .gif  image/gif



5. Web server deployment:
==========================

To deploy the web server, first create the web configuration file in the
format mentioned the previous section. Also put all the web pages that
need to be rendered in a "www" folder and mentioned the absolute path to the
"www" in the configuration file. Now start the server (section 3.3).

Eg: 	+ src
           +-- httpd
	   +-- *.cc files
	   +-- include
	        +-- *.h files
	   +-- ws.conf

	+ www
	  + images
	  + html pages


6. Release:
============



7. Bibiliography:
====================

* https://en.wikipedia.org/wiki/Web_server
* http://www.w3.org/Protocols/rfc2616/rfc2616.html


8. Bugs:
=========

Please reports the bugs to sunhick@gmail.com
