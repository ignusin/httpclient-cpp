#include "chunked_buffer_reader.hpp"
#include "http_conversions.hpp"
#include "http_empty_body.hpp"
#include "http_form_body.hpp"
#include "http_string_body.hpp"
#include "http_utility.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace hc = httpclient;

std::optional<hc::http_status_code> hc::make_status_code(const hc::chunked_buffer &buffer)
{
    auto str = make_string(buffer);

    auto pos1 = str.find_first_of(' ');
    if (pos1 == std::string::npos)
    {
        return {};
    }

    auto pos2 = str.find_first_of("\n ", pos1 + 1);
    if (pos2 == std::string::npos)
    {
        return {};
    }

    auto status_code_str = str.substr(pos1 + 1, pos2 - pos1 - 1);
    unsigned int status_code;
    
    std::istringstream ss{status_code_str};
    ss >> status_code;

    if (ss.fail())
    {
        return {};
    }

    if (str[pos2] == '\n')
    {
        return hc::http_status_code{status_code, ""};
    }

    auto pos3 = str.find_first_of('\n', pos2 + 1);
    if (pos3 == std::string::npos)
    {
        return {};
    }

    auto status_text = str.substr(pos2 + 1, pos3 - pos2 - 1);

    return hc::http_status_code{status_code, status_text};
}

static std::optional<std::pair<std::string, std::string>> make_single_header(
    const std::string& header_line)
{
    auto sc_pos = header_line.find_first_of(':');
    if (sc_pos == std::string::npos)
    {
        return {};
    }

    auto header_name = header_line.substr(0, sc_pos);
    auto header_value = header_line.substr(sc_pos + 2);

    return std::pair{header_name, header_value};
}

hc::http_headers hc::make_headers(const hc::chunked_buffer &buffer)
{
    auto str = make_string(buffer);

    hc::http_headers result;

    auto pos_prev = -1;
    auto pos = str.find_first_of('\n');
    while (pos != std::string::npos)
    {
        auto line = str.substr(pos_prev + 1, pos - pos_prev - 1);
        
        auto header = make_single_header(line);
        if (header)
        {
            const auto &header_value = *header;
            result.append(header_value.first, header_value.second);
        }

        pos_prev = pos;
        pos = str.find_first_of('\n', pos + 1);
    }

    return result;
}

std::string hc::make_string(const hc::chunked_buffer &buffer)
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

    return str;
}

template<>
hc::chunked_buffer hc::make_buffer<hc::http_empty_body>(const hc::http_empty_body &body)
{
    return {};
}

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
    return hc::http_string_body{make_string(buffer)};
}
