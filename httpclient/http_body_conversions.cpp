#include "chunked_buffer_reader.hpp"
#include "http_body_conversions.hpp"
#include "http_form_body.hpp"
#include "http_string_body.hpp"
#include "http_utility.hpp"
#include <sstream>

namespace hc = httpclient;

template<>
hc::chunked_buffer hc::make_buffer<hc::http_form_body>(const hc::http_form_body &body)
{
    std::ostringstream os;
    bool has_first = false;

    for (auto it = body.values_begin(); it != body.values_end(); ++it)
    {
        const auto &pair = *it;

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

template<>
hc::http_string_body hc::make_body<hc::http_string_body>(const chunked_buffer &buffer)
{
    uint8_t bytes[2048];

    hc::chunked_buffer_reader reader{buffer};

    std::string str;
    
    unsigned int read_count = reader.read(bytes, sizeof(bytes));
    while (read_count > 0)
    {
        str.append(reinterpret_cast<char *>(bytes), read_count);
        read_count = reader.read(bytes, sizeof(bytes));
    }

    return hc::http_string_body{std::move(str)};
}
