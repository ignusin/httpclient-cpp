#include "http_utility.hpp"

namespace hc = httpclient;

std::string http_url_encode(const std::string &value);
std::string http_url_decode(const std::string &value);
