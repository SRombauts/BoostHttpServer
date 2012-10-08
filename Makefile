
### Options: ###

# C++ compiler 
CXX = g++

# flags for C++
CXXFLAGS ?= -Wall -Wextra -pedantic -pedantic -Wformat-security -Winit-self -Wswitch-default -Wswitch-enum -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wconversion -Wlogical-op -Winline -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn

# [Debug,Release]
BUILD ?= Debug

### Conditionally set variables: ###

ifeq ($(BUILD),Debug)
BUILD_FLAGS = -g3 -rdynamic -fstack-protector-all -fno-inline -O0 -DDEBUG -D_DEBUG
endif
ifeq ($(BUILD),Release)
BUILD_FLAGS = -O2
endif
ifeq ($(BUILD),Debug)
LINK_FLAGS = -g3 -rdynamic
endif
ifeq ($(BUILD),Release)
LINK_FLAGS =
endif

### Variables: ###

CPPDEPS = -MT $@ -MF`echo $@ | sed -e 's,\.o$$,.d,'` -MD -MP

BOOST_HTTP_SERVER_CXXFLAGS = $(BUILD_FLAGS) $(CXXFLAGS)
BOOST_HTTP_SERVER_EXAMPLE1_OBJECTS =  \
	$(BUILD)/BoostHttpServer_posix_main.o \
	$(BUILD)/BoostHttpServer_connection.o \
	$(BUILD)/BoostHttpServer_connection_manager.o \
	$(BUILD)/BoostHttpServer_mime_types.o \
	$(BUILD)/BoostHttpServer_reply.o \
	$(BUILD)/BoostHttpServer_request_handler.o \
	$(BUILD)/BoostHttpServer_request_parser.o \
	$(BUILD)/BoostHttpServer_server.o
	
BOOST_HTTP_SERVER_EXAMPLE2_OBJECTS =  \
	$(BUILD)/BoostHttpServer_main.o \
	$(BUILD)/BoostHttpServer_connection.o \
	$(BUILD)/BoostHttpServer_connection_manager.o \
	$(BUILD)/BoostHttpServer_mime_types.o \
	$(BUILD)/BoostHttpServer_reply.o \
	$(BUILD)/BoostHttpServer_request_handler.o \
	$(BUILD)/BoostHttpServer_request_parser.o \
	$(BUILD)/BoostHttpServer_server.o
	
### Targets: ###

all: $(BUILD) $(BUILD)/example1_static $(BUILD)/example2_dynamic

clean: 
	rm -f $(BUILD)/*.o
	rm -f $(BUILD)/*.d
	rm -f $(BUILD)/example1_static
	rm -f $(BUILD)/example2_dynamic

$(BUILD): $(BUILD)/
	mkdir -p $(BUILD)

$(BUILD)/example1_static: $(BOOST_HTTP_SERVER_EXAMPLE1_OBJECTS)
	$(CXX) -o $@ $(BOOST_HTTP_SERVER_EXAMPLE1_OBJECTS) $(LINK_FLAGS) -lboost_system-mt -lboost_thread-mt -lboost_filesystem-mt


$(BUILD)/example2_dynamic: $(BOOST_HTTP_SERVER_EXAMPLE2_OBJECTS)
	$(CXX) -o $@ $(BOOST_HTTP_SERVER_EXAMPLE2_OBJECTS) $(LINK_FLAGS) -lboost_system -lboost_filesystem


$(BUILD)/BoostHttpServer_posix_main.o: src/example1_static/posix_main.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<


$(BUILD)/BoostHttpServer_main.o: src/example2_dynamic/main.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<


$(BUILD)/BoostHttpServer_connection.o: src/server/connection.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

$(BUILD)/BoostHttpServer_connection_manager.o: src/server/connection_manager.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

$(BUILD)/BoostHttpServer_mime_types.o: src/server/mime_types.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

$(BUILD)/BoostHttpServer_reply.o: src/server/reply.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

$(BUILD)/BoostHttpServer_request_handler.o: src/server/request_handler.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

$(BUILD)/BoostHttpServer_request_parser.o: src/server/request_parser.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<

$(BUILD)/BoostHttpServer_server.o: src/server/server.cpp
	$(CXX) -c -o $@ $(BOOST_HTTP_SERVER_CXXFLAGS) $(CPPDEPS) $<


.PHONY: all clean


# Dependencies tracking:
-include $(BUILD)/*.d

