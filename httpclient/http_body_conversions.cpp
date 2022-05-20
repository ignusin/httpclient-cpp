#include "http_body_conversions.hpp"
#include "http_form_body.hpp"
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
