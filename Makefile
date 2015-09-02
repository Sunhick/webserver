#
# Make file for Web Server
# 

CC = g++
LDFLAGS =
CCFLAGS = -g -Wall -std=c++11

all: test

test: test.o ConfigParser.o
	$(CC) $(CCFLAGS) test.o ConfigParser.o -o test

ConfigParser.o: ConfigParser.h ConfigParser.cc
	$(CC) $(CCFLAGS) -c ConfigParser.cc

test.o: test.cc
	$(CC) $(CCFLAGS) -c test.cc

clean:
	-rm *.o *~ test
