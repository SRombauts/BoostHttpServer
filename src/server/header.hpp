///
/// \file header.hpp
///
/// Structure of a header in a HTTP request or reply.
/// 
/// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
/// Copyright (c) 2012-2017 Sebastien Rombauts (sebastien.rombauts@gmail.com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///

#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include <string>
#include <vector>

namespace http {
namespace server {

/// Structure of a header in a HTTP request or reply
struct header
{
  std::string name;   ///< normalized name of the header
  std::string value;  ///< string value of the header
};

/// List of HTTP headers.
typedef std::vector<header> headers_list;

} // namespace server
} // namespace http

#endif // HTTP_HEADER_HPP
