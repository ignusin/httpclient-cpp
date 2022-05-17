#ifndef __HTTP_REQUEST_HPP__
#define __HTTP_REQUEST_HPP__

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
    
        t_body _body;

    public:
        http_request(http_verb verb, const std::string &url, const t_body &body = t_body())
            : _verb(verb), _url(url), _body(body)
        {
        }

        http_verb verb() const { return _verb; }

        const std::string &url() const { return _url; } 

        const t_body &body() const { return _body; }
    };
}

#endif // __HTTP_REQUEST_HPP__