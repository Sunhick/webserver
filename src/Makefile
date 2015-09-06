#
# Author: Sunil bn <suba5417@colorado.edu>
# Make file for Web Server
# 

CC = g++
DEBUG = -g
LDFLAGS = -pthread
CCFLAGS = -Wall -std=c++11 $(DEBUG) -I $(IDIR)

IDIR = ./include
Exe = httpd

SRC = test.cc ConfigParser.cc WebServer.cc
OBJS = $(SRC:.cc=.o)

all: $(Exe)

$(Exe): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(Exe)

%.o: %.cc
	$(CC) -c -o $@ $(CCFLAGS) $<

.PHONY: clean
clean:
	@rm $(OBJS) $(Exe) *~ include/*~

# create a web server source tar ball 
tar:
	tar cvf webserver.tar *.* include/*.*
