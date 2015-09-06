#
# Make file for Web Server
# 

CC = g++
LDFLAGS = -pthread
CCFLAGS = -g -Wall -std=c++11 -I $(IDIR)

IDIR = ./include
Exe = httpd
OBJS = test.o ConfigParser.o WebServer.o

all: $(Exe)

$(Exe): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(Exe)

%.o: %.cc
	$(CC) -c -o $@ $(CCFLAGS) $<

.PHONY: clean
clean:
	rm *.o *~ $(Exe)
