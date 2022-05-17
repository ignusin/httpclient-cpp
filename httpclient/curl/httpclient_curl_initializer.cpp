#include "httpclient_curl_initializer.hpp"
#include <curl/curl.h>


httpclient::curl::httpclient_curl_initializer::httpclient_curl_initializer()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

httpclient::curl::httpclient_curl_initializer::~httpclient_curl_initializer()
{
    curl_global_cleanup();
}
