#include "http_headers.hpp"

namespace hc = httpclient;


void hc::http_headers::append(const std::string &key, const std::string &value)
{
    auto it = _values.find(key);
    if (it == _values.end())
    {
        _values[key] = std::list<std::string>{value};
    }
    else
    {
        it->second.push_back(value);
    }
}

hc::http_header_values::const_iterator hc::http_headers::begin() const
{
    return _values.begin();
}

hc::http_header_values::const_iterator hc::http_headers::end() const
{
    return _values.end();
}
