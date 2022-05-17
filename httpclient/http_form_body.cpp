#include "http_form_body.hpp"

namespace hc = httpclient;

void hc::http_form_body::append(const std::string &key, const std::string &value)
{
    _values.push_back(hc::http_key_value{key, value});
}
