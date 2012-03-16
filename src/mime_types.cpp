//
// mime_types.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "mime_types.hpp"

namespace http {
namespace server {
namespace mime_types {

// mapping of mime types by extension
struct mapping
{
  const char* extension;
  const char* mime_type;
} mappings[] =
{
  // no extension
  { "",     "text/plain" },
  // common text mime types
  { "htm",  "text/html" },
  { "html", "text/html" },
  { "css",  "text/css"  },
  { "js",   "application/x-javascript" },
  { "xml",  "text/xml" },
  { "xhtml","application/xhtml+xml" },
  { "txt",  "text/plain" },
  { "csv",  "text/csv"  },
  { "latex","application/x-latex" },
  // common image mime types
  { "jpeg","image/jpeg" },
  { "jpg", "image/jpeg" },
  { "jpe", "image/jpeg" },
  { "png", "image/png" },
  { "svg", "image/svg+xml" },
  { "ico", "image/vnd.microsoft.icon" },
  { "gif", "image/gif" },
  { "tiff","image/tiff" },
  { "tif", "image/tiff" },
  { "bmp", "image/bmp" },
  // common compressed file
  { "zip", "application/zip" },
  { "gz",  "application/x-gzip" },
  { "bz2", "application/x-bzip2" },
  { "7z",  "application/x-7z-compressed" },
  { "rar", "application/x-rar-compressed" },
  { "tar", "application/x-tar" },
  // common media file
  { "mp3", "audio/mpeg" },
  { "mpeg","video/mpeg" },
  { "mpg", "video/mpeg" },
  { "ogg", "audio/ogg" },
  { "wav", "audio/vnd.wave" },
  { "swf", "application/x-shockwave-flash" },
  { "pdf", "application/pdf" },
  // common OpenDocument mime types
  { "odt", "application/vnd.oasis.opendocument.text" },
  { "ods", "application/vnd.oasis.opendocument.spreadsheet" },
  { "odp", "application/vnd.oasis.opendocument.presentation" },
  { "odg", "application/vnd.oasis.opendocument.graphics" },
  { "odc", "application/vnd.oasis.opendocument.chart" },
  { "odf", "application/vnd.oasis.opendocument.formula" },
  { "odb", "application/vnd.oasis.opendocument.database" },
  { "odi", "application/vnd.oasis.opendocument.image" },
  { "odm", "application/vnd.oasis.opendocument.text-master" },
  { "ott", "application/vnd.oasis.opendocument.text-template" },
  { "ots", "application/vnd.oasis.opendocument.spreadsheet-template" },
  { "otp", "application/vnd.oasis.opendocument.presentation-template" },
  { "otg", "application/vnd.oasis.opendocument.graphics-template" },
  // common Microsoft Office mime types
  { "doc", "application/msword" },
  { "dot", "application/msword" },
  { "docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document" },
  { "dotx", "application/vnd.openxmlformats-officedocument.wordprocessingml.template" },
  { "xls", "application/vnd.ms-excel" },
  { "xlt", "application/vnd.ms-excel" },
  { "xla", "application/vnd.ms-excel" },
  { "xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet" },
  { "xltx", "application/vnd.openxmlformats-officedocument.spreadsheetml.template" },
  { "ppt", "application/vnd.ms-powerpoint" },
  { "pot", "application/vnd.ms-powerpoint" },
  { "pps", "application/vnd.ms-powerpoint" },
  { "ppa", "application/vnd.ms-powerpoint" },
  { "pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation" },
  { "potx", "application/vnd.openxmlformats-officedocument.presentationml.template" },
  { "ppsx", "application/vnd.openxmlformats-officedocument.presentationml.slideshow" },
  { 0, 0 } // Marks end of list.
};

std::string extension_to_type(const std::string& extension)
{
  for (mapping* m = mappings; m->extension; ++m)
  {
    if (m->extension == extension)
    {
      return m->mime_type;
    }
  }

  return "text/plain";
}

} // namespace mime_types
} // namespace server
} // namespace http
