###############################################
#
# Make file for Web Server
# Author: Sunil bn <suba5417@colorado.edu>
#
# ############################################

CC = g++
DEBUG = -g
LDFLAGS = -pthread
CCFLAGS = -Wall -std=c++11 $(DEBUG) -I $(IDIR)

IDIR = ./include
Exe = httpd

# Discover all .cc files in src/ and try to compile them
SRC = $(wildcard *.cc)
OBJS = $(SRC:.cc=.o)

TARBALL = webserver.tar.gz

all: $(Exe)

$(Exe): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(Exe)

%.o: %.cc
	$(CC) -c -o $@ $(CCFLAGS) $<

.PHONY: clean
clean:
	@rm $(OBJS) $(Exe) *~ include/*~ $(TARBALL)

# create a web server source tar ball 
tar:
	tar -cvzf $(TARBALL) *.* include/*.* README
