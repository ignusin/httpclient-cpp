#ifndef __HTTP_BODY_HPP__
#define __HTTP_BODY_HPP__

#include "chunked_buffer.hpp"

namespace httpclient
{
    class http_body
    {
    public:
        virtual ~http_body();
        virtual chunked_buffer to_buffer() const = 0;
    };
}

#endif // __HTTP_BODY_HPP__
