///
/// \file request_handler.hpp
///
/// Handle a HTTP request by returning the client the resource he asked.
///
/// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
///
/// Distributed under the Boost Software License, Version 1.0. (See accompanying
/// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///

#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <map>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

namespace http {
namespace server {

struct reply;
struct request;

/// Map of options by name/values
typedef std::map<std::string, std::string> params_map;

/// Prototype of a function able to generate a reply for the provided client request
typedef boost::function<void (const request& req, const params_map& params, reply& rep)>  resource_function;

/// The common handler for all incoming requests.
class request_handler
  : private boost::noncopyable
{
public:
  /// Construct with a directory containing files to be served.
  explicit request_handler(const std::string& doc_root);

  /// Handle a request and produce a reply.
  void handle_request(const request& req, reply& rep);

  /// Register a dynamic resource (a code generated web page)
  void register_resource(const std::string& resource_name, resource_function& function);
  void unregister_resource(const std::string& resource_name);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);

  /// Tokenize the query part of the URI, splitting it by option name/values.
  static void query_tokenize(const std::string& in, params_map& out);

  /// Map of a functions able to generate a reply for the provided client request
  typedef std::map<std::string, resource_function>  resource_map;

  /// Map of a functions able to generate a reply for the provided client request
  resource_map  resource_map_;
};

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP
