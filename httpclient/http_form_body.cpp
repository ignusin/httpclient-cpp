#include "http_form_body.hpp"
#include "chunked_buffer.hpp"
#include "http_utility.hpp"

#include <sstream>

namespace hc = httpclient;

void hc::http_form_body::append(const std::string &key, const std::string &value)
{
    _values.push_back(hc::http_key_value{key, value});
}

hc::chunked_buffer hc::http_form_body::to_buffer() const
{
    std::ostringstream os;
    bool has_first = false;

    for (const auto &pair : _values)
    {
        if (has_first)
        {
            os << "&";
        }

        os << hc::http_url_encode(pair.first) << "=" << hc::http_url_encode(pair.second);
        has_first = true;
    }

    std::string s = os.str();
    unsigned int size = s.size();

    hc::chunked_buffer result;
    result.append(hc::chunked_buffer::chunk(reinterpret_cast<const uint8_t *>(s.c_str()), size));

    return result;
}


