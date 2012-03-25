///
/// @file   header.hpp
/// @module server
/// @brief  Structure of a HTTP header in the reply
/// 

//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include <string>

namespace http {
namespace server {

/// Structure of a HTTP header in the reply
struct header
{
  std::string name;   ///< normalized name of the header
  std::string value;  ///< string value of the header
};

} // namespace server
} // namespace http

#endif // HTTP_HEADER_HPP
