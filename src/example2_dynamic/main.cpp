///
/// \file main.cpp
///
/// Portable entry point for dynamic web page generation example.
///
/// This sample demonstrate the way to fully generate by code a website,
/// and to stop cleanly the server from a webpage.
///
/// Copyright (c) 2012 Sebastien Rombauts (sebastien dot rombauts at gmail dot com)
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

/// Function to generate the our first dynamic resource : web page "/"
/// TODO : unused parameters req
void on_request_page_root (const http::server::request& req, http::server::reply& rep)
{
  rep.status = http::server::reply::ok;
  rep.content = "<html><head><title>Welcome</title></head><body><a href=\"/stop\">stop</a></body></html>";
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "text/html";
}

/// Function to generate the our first dynamic resource, and ask the server to stop : web page "/stop"
/// TODO : unused parameters req
void on_request_page_stop (const http::server::request& req, http::server::reply& rep, http::server::server* serv)
{
  rep.status = http::server::reply::ok;
  rep.content = "<html>stopped</html>";
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "text/html";
  
  // ask asynchronously the server to stop : we will get our stop page before
  serv->stop ();
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
    http::server::resource_function function_on_request_page_root = boost::bind(on_request_page_root, _1, _2);
    http::server::resource_function function_on_request_page_stop = boost::bind(on_request_page_stop, _1, _2, &serv);

    serv.register_resource("/",    function_on_request_page_root);
    serv.register_resource("/stop",function_on_request_page_stop);

    // Run the server until stopped.
    serv.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
