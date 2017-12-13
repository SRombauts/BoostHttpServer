///
/// \file main.cpp
///
/// Portable entry point for dynamic web page generation example.
///
/// This sample demonstrate the way to fully generate by code a website,
/// and to stop cleanly the server from a webpage.
///
/// Copyright (c) 2012-2017 Sebastien Rombauts (sebastien.rombauts@gmail.com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include "../server/server.hpp"

#include "../../CTML/CTML/CTML.h"

/// Function to generate our first dynamic resource : root "/" web page
void on_request_page_root (const http::server::request& /*req*/, const http::server::params_map& /*params*/, http::server::reply& rep)
{
//rep.content = "<html><head><title>Welcome</title></head><body><p>Welcome</p><a href=\"/stop\">stop</a></body></html>";
  CTML::Document document;
  document.AddNodeToHead(CTML::Node("title", "Welcome"));
  document.AddNodeToBody(CTML::Node("p", "Welcome"));
  document.AddNodeToBody(CTML::Node("a", "stop").SetAttribute("href", "/stop"));
  rep.content = document.ToString(CTML::Readability::MULTILINE);
  rep.headers.push_back(http::server::header{"Content-Type", "text/html"});
  rep.status = http::server::reply::ok;
}

/// Generate content for the "/stop" web page, display a confirmation link, and ask the server to stop if confirmed
void on_request_page_stop (const http::server::request& /*req*/, const http::server::params_map& params, http::server::reply& rep, http::server::server* serv)
{
  if (params.find("confirm") != params.end())
  {
	  // ask asynchronously the server to stop : we will get our stop page before
	  serv->stop();
	  rep.content = "<html><head><title>Stopped</title><body><p>Stopped</p></body></html>";
  }
  else
  {
	  rep.content = "<html><head><title>Stop</title><body><p>Stop</p><a href=\"/\">back</a><br/><a href=\"/stop?confirm\">confirm</a></body></html>";
  }
  rep.headers.push_back(http::server::header{"Content-Type", "text/html"});
  rep.status = http::server::reply::ok;
}


int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 4)
    {
      std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    http_server 0.0.0.0 80 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    http_server 0::0 80 .\n";
      return 1;
    }

    // Initialise server.
    http::server::server serv(argv[1], argv[2], argv[3]);

    // Register our two dynamic resources (web page "/" and "/stop")
    serv.register_resource("/",      http::server::resource_function(boost::bind(on_request_page_root, _1, _2, _3)));
    serv.register_resource("/stop",  http::server::resource_function(boost::bind(on_request_page_stop, _1, _2, _3, &serv)));

    // Run the server until stopped.
    serv.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
