#
# Make file for Web Server
# 

CC = g++
LDFLAGS = -pthread
CCFLAGS = -g -Wall -std=c++11 -I $(IDIR)

IDIR = ./include

OBJS = test.o ConfigParser.o WebServer.o

all: test

test: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o test

%.o: %.cc
	$(CC) -c -o $@ $< $(CCFLAGS)

.PHONY: clean
clean:
	rm *.o *~ test
