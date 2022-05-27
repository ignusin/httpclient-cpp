#ifndef __HTTP_RESPONSE_HPP__
#define __HTTP_RESPONSE_HPP__

#include "http_status_code.hpp"
#include "http_headers.hpp"

namespace httpclient
{
    template<typename t_body>
    class http_response
    {
    private:
        http_status_code _status_code;
        http_headers _headers;
        t_body _body;

    public:
        http_response(
            http_status_code &&status_code,
            http_headers &&headers,
            t_body &&body = t_body()) :
                _status_code(std::move(status_code)),
                _headers(std::move(headers)),
                _body(std::move(body))
        {
        }

        const t_body &body() const
        {
            return _body;
        }
    };
}

#endif // __HTTP_RESPONSE_HPP__
