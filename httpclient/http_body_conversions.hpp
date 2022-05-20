#ifndef __HTTP_BODY_CONVERSIONS_HPP__
#define __HTTP_BODY_CONVERSIONS_HPP__

#include "chunked_buffer.hpp"

namespace httpclient
{
    template<typename t_body>
    t_body make_body(const chunked_buffer &buffer);

    template<typename t_body>
    chunked_buffer make_buffer(const t_body &body);
}

#endif // __HTTP_BODY_CONVERSIONS_HPP__
