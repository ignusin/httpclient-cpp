#include "http_string_body.hpp"

namespace hc = httpclient;

hc::http_string_body::http_string_body(std::string &&content)
    : _content(std::move(content))
{
}

const std::string &hc::http_string_body::content() const
{
    return _content;
}
