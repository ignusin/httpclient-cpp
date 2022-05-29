#ifndef __HTTP_REQUEST_HPP__
#define __HTTP_REQUEST_HPP__

#include "http_headers.hpp"
#include <string>

namespace httpclient
{
    enum http_verb
    {
        http_get = 1,
        http_post,
    };

    // TODO: copyable, movable.
    // TODO: t_body is copyable, movable.
    template<typename t_body>
    class http_request
    {
    private:
        http_verb _verb;
        std::string _url;
        http_headers _headers;    
        t_body _body;

    public:
        http_request(
            http_verb verb,
            const std::string &url,
            http_headers &&headers = http_headers(),
            t_body &&body = t_body()) :
                _verb(verb),
                _url(url),
                _headers(std::move(headers)),
                _body(std::move(body))
        {
        }

        http_verb verb() const { return _verb; }

        const std::string &url() const { return _url; } 

        const http_headers &headers() const { return _headers; }

        const t_body &body() const { return _body; }
    };
}

#endif // __HTTP_REQUEST_HPP__