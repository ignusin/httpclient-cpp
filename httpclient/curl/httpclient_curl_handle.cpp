#include "httpclient_curl_handle.hpp"

httpclient::curl::httpclient_curl_handle::httpclient_curl_handle()
{
    _handle = curl_easy_init();
}

httpclient::curl::httpclient_curl_handle::~httpclient_curl_handle()
{
    if (!this)
    {
        return;
    }

    curl_easy_cleanup(handle());
}

CURL* httpclient::curl::httpclient_curl_handle::handle() const
{
    return _handle;
}

CURL* httpclient::curl::httpclient_curl_handle::operator*() const
{
    return handle();
}

httpclient::curl::httpclient_curl_handle::operator bool() const
{
    return !!handle();
}
