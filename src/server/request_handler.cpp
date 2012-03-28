///
/// \file request_handler.cpp
/// 
/// Handle a HTTP request by returning the client the resource he asked.
///
/// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace http {
namespace server {

request_handler::request_handler(const std::string& doc_root)
  : doc_root_(doc_root)
{
}

void request_handler::handle_request(const request& req, reply& rep)
{
  // Decode url to path.
  std::string request_path;
  if (!url_decode(req.uri, request_path))
  {
    reply::stock_reply(reply::bad_request, rep);
    return;
  }

  // Decode and tokenize the query part of the URI
  std::string query;
  options_map get_params;
  if (!url_decode(req.query, query))
  {
    reply::stock_reply(reply::bad_request, rep);
    return;
  }
  query_tokenize (query, get_params);

  // Decode and tokenize the content part of the POST request
  std::string content;
  options_map post_params;
  if (!url_decode(req.content, content))
  {
    reply::stock_reply(reply::bad_request, rep);
    return;
  }
  query_tokenize (content, post_params);

  // Check if the request is for a registered dynamic resource
  resource_map::iterator resource = resource_map_.find(request_path);
  if (resource_map_.end() != resource)
  {
    // A dynamic web page will be generated in reply to the client request
    (*resource).second (req, rep);
    return;
  }

  // Request path must be absolute and not contain "..".
  if (request_path.empty() || request_path[0] != '/'
      || request_path.find("..") != std::string::npos)
  {
    reply::stock_reply(reply::bad_request, rep);
    return;
  }

  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (request_path[request_path.size() - 1] == '/')
  {
    request_path += "index.html";
  }
  else
  {
    // If it does not end in a slash, but is a directory, then redirect to the slash terminated path
    if (boost::filesystem::is_directory(doc_root_ + request_path))
    {
      reply::redirect_reply(request_path + "/", rep);
      return;
    }
  }

  // Determine the file extension.
  std::size_t last_slash_pos = request_path.find_last_of("/");
  std::size_t last_dot_pos = request_path.find_last_of(".");
  std::string extension;
  if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
  {
    extension = request_path.substr(last_dot_pos + 1);
  }

  // Open the file to send back.
  std::string full_path = doc_root_ + request_path;
  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  if (!is)
  {
    reply::stock_reply(reply::not_found, rep);
    return;
  }

  // Fill out the reply to be sent to the client.
  rep.status = reply::ok;
  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0)
    rep.content.append(buf, (unsigned int)is.gcount());
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = mime_types::extension_to_type(extension);
}

bool request_handler::url_decode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}

void request_handler::query_tokenize(const std::string& in, options_map& out)
{
  bool        in_option_name = true;
  std::string option_name;
  std::string option_value;

  out.clear();

  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in_option_name)
    {
      // parsing the name of an option
      if (in[i] == '=')
      {
        in_option_name = false;
      }
      else if (in[i] == '&')
      {
        out[option_name] = ""; // option without value
        option_name.clear ();
      }
      else
      {
        option_name += in[i];
      }
    }
    else
    {
      // parsing the value of an option
      if (in[i] == '&')
      {
        out[option_name] = option_value; // option with value
        option_name.clear ();
        option_value.clear ();
        in_option_name = true;
      }
      else
      {
        option_value += in[i];
      }
    }
  }

  if (false == option_name.empty())
  {
    out[option_name] = option_value; // last option with or without value
  }
}

/// Register a dynamic resource (a code generated web page)
void request_handler::register_resource(const std::string& resource_name, resource_function& function)
{
  resource_map_.insert(std::pair<std::string, resource_function>(resource_name, function));
}

/// Unegister a dynamic resource
void request_handler::unregister_resource(const std::string& resource_name)
{
  resource_map::iterator resource = resource_map_.find(resource_name);
  if (resource_map_.end() != resource)
  {
    resource_map_.erase(resource);
  }
}

} // namespace server
} // namespace http
