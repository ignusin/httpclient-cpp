#include "http_status_code.hpp"

namespace hc = httpclient;

hc::http_status_code::http_status_code(const unsigned int code, const std::string &text)
    : _code(code), _text(text)
{
}

unsigned int hc::http_status_code::code() const
{
    return _code;
}

const std::string &hc::http_status_code::text() const
{
    return _text;
}
