#include "httpclient_curl_slist.hpp"
#include <sstream>

namespace hc = httpclient;

hc::curl::httpclient_curl_slist::~httpclient_curl_slist()
{
    if (_list)
    {
        curl_slist_free_all(_list);
    }

    _list = nullptr;
}

void hc::curl::httpclient_curl_slist::append(const std::string &name, const std::string &value)
{
    std::ostringstream ss;
    ss << name << ": " << value;

    _list = curl_slist_append(_list, ss.str().c_str());
}

const curl_slist *hc::curl::httpclient_curl_slist::list() const
{
    return _list;
}