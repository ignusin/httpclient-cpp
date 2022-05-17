#include "httpclient_curl_handle.hpp"

namespace hc = httpclient;

hc::curl::httpclient_curl_handle::httpclient_curl_handle()
{
    _handle = curl_easy_init();
}

hc::curl::httpclient_curl_handle::~httpclient_curl_handle()
{
    if (!this)
    {
        return;
    }

    curl_easy_cleanup(handle());
}

CURL* hc::curl::httpclient_curl_handle::handle() const
{
    return _handle;
}

CURL* hc::curl::httpclient_curl_handle::operator*() const
{
    return handle();
}

hc::curl::httpclient_curl_handle::operator bool() const
{
    return !!handle();
}
