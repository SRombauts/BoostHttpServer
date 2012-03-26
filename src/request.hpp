///
/// @file   request.hpp
/// @module server
/// @brief  Structure of a HTTP request
/// 

//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include "header.hpp"

namespace http {
namespace server {

/// A request received from a client.
struct request
{
  std::string method;
  std::string uri;
  std::string query;
  std::string fragment;
  int         http_version_major;
  int         http_version_minor;
  headers_list headers;
  size_t      content_length;
  std::string content;
};

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_HPP
