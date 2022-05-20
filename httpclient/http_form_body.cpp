#include "http_form_body.hpp"
#include "chunked_buffer.hpp"
#include "http_utility.hpp"

#include <sstream>

namespace hc = httpclient;

void hc::http_form_body::append(const std::string &key, const std::string &value)
{
    _values.push_back(hc::http_key_value{key, value});
}

std::list<hc::http_key_value>::const_iterator hc::http_form_body::values_begin() const
{
    return _values.begin();
}

std::list<hc::http_key_value>::const_iterator hc::http_form_body::values_end() const
{
    return _values.end();
}
