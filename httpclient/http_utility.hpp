#ifndef __HTTP_UTILITY_HPP__
#define __HTTP_UTILITY_HPP__

#include <string>

namespace httpclient
{
    std::string http_url_encode(const std::string &value);
    std::string http_url_decode(const std::string &value);
}

#endif // __HTTP_UTILITY_HPP__
