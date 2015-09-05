#
# Make file for Web Server
# 

CC = g++
LDFLAGS =
CCFLAGS = -g -Wall -std=c++11

OBJS = test.o ConfigParser.o WebServer.o

all: test

test: test.o ConfigParser.o WebServer.o
	$(CC) $(CCFLAGS) $(OBJS) -o test

ConfigParser.o: ConfigParser.h ConfigParser.cc
	$(CC) $(CCFLAGS) -c ConfigParser.cc

test.o: test.cc
	$(CC) $(CCFLAGS) -c test.cc

WebServer.o: WebServer.cc WebServer.h
	$(CC) $(CCFLAGS) -c WebServer.cc

clean:
	-rm *.o *~ test
