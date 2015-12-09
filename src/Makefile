###############################################
#
# Make file for Web Server
# Author: Sunil bn <sunhick@gmail.com>
#
###############################################
CC = g++
DEBUG = -g -O0
LDFLAGS = -pthread
CCFLAGS = -Wall -std=c++11 $(DEBUG) -I $(IDIR)

IDIR = ./include
Exe = httpd

# Discover all .cc files in src/ and try to compile them
SRC = $(wildcard *.cc)
OBJS = $(SRC:.cc=.o)

TARBALL = webserver.tar.gz

GCCVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')
GCC_MIN = "4.8.2"   # Min g++ version = 4.8 to support c++11 options

ifeq ($(USE_IP), 1)
	DEBUG += -DUSE_IP
# @echo 'Building with -D USE_IP feature...'
endif

all: $(Exe)

$(Exe): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(Exe)

%.o: %.cc
	$(CC) -c -o $@ $(CCFLAGS) $<

# Verify the compiler version which supports c++11
# verify:
#	@echo checking g++ version : $(GCCVERSION)
# ifeq ($(GCCVERSION), $(GCC_MIN))
# 	@echo g++ verison supports c++11 flag!
# else
#	$(error current g++ version does not support c++11. Please update g++ to 4.8 or above)
# endif

.PHONY: clean
clean:
	@rm $(OBJS) $(Exe) *~ include/*~ $(TARBALL)

# create a web server source tar ball 
tar:
	tar -cvzf $(TARBALL) *.* include/*.* README Makefile
