
# options:

AR ?= ar
RANLIB ?= ranlib

# C++ compiler 
CXX = g++

# flags for C++ 
CXXFLAGS ?= -Wall

# [Debug,Release]
BUILD ?= Debug

### Conditionally set variables: ###

ifeq ($(BUILD),Debug)
BUILD_FLAGS = -g -rdynamic -fno-inline -O0 -DDEBUG -D_DEBUG
endif
ifeq ($(BUILD),Release)
BUILD_FLAGS = -O2
endif
ifeq ($(BUILD),Debug)
LINK_FLAGS = -g -rdynamic
endif
ifeq ($(BUILD),Release)
LINK_FLAGS =
endif

### Variables: ###

CPPDEPS = -MT$@ -MF`echo $@ | sed -e 's,\.o$$,.d,'` -MD -MP

BOOST_HTTP_SERVER_CXXFLAGS = -pthread $(BUILD_FLAGS) $(CXXFLAGS)
BOOST_HTTP_SERVER_OBJECTS =  \
	BoostHttpServer_connection.o \
	BoostHttpServer_connection_manager.o \
	BoostHttpServer_mime_types.o \
	BoostHttpServer_posix_main.o \
	BoostHttpServer_reply.o \
	BoostHttpServer_request_handler.o \
	BoostHttpServer_request_parser.o \
	BoostHttpServer_server.o
	
### Targets: ###

all: BoostHttpServer

install: 

uninstall: 

clean: 
	rm -f ./*.o
	rm -f ./*.d
	rm -f BoostHttpServer


BoostHttpServer: $(BOOST_HTTP_SERVER_OBJECTS)
	$(CXX) -o $@ $(BOOST_HTTP_SERVER_OBJECTS) -pthread $(LINK_FLAGS) -lboost_thread-mt -lboost_system-mt -lboost_filesystem-mt


BoostHttpServer_connection.o: src/connection.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

BoostHttpServer_connection_manager.o: src/connection_manager.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

BoostHttpServer_mime_types.o: src/mime_types.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

BoostHttpServer_posix_main.o: src/posix_main.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

BoostHttpServer_reply.o: src/reply.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

BoostHttpServer_request_handler.o: src/request_handler.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

BoostHttpServer_request_parser.o: src/request_parser.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

BoostHttpServer_server.o: src/server.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<



.PHONY: all install uninstall clean


# Dependencies tracking:
-include ./*.d
