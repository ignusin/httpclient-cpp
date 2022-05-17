#include "httpclient_curl_initializer.hpp"
#include <curl/curl.h>

namespace hc = httpclient;

hc::curl::httpclient_curl_initializer::httpclient_curl_initializer()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

hc::curl::httpclient_curl_initializer::~httpclient_curl_initializer()
{
    curl_global_cleanup();
}
