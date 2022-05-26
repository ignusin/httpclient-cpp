#ifndef __HTTP_BODY_CONVERSIONS_HPP__
#define __HTTP_BODY_CONVERSIONS_HPP__

#include "chunked_buffer.hpp"
#include "http_status_code.hpp"
#include "http_headers.hpp"

namespace httpclient
{
    http_status_code make_status_code(const chunked_buffer &buffer);

    http_headers make_headers(const chunked_buffer &buffer);

    template<typename t_body>
    t_body make_body(const chunked_buffer &buffer);

    template<typename t_body>
    chunked_buffer make_buffer(const t_body &body);
}

#endif // __HTTP_BODY_CONVERSIONS_HPP__
