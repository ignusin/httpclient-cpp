#ifndef __HTTP_RESPONSE_HPP__
#define __HTTP_RESPONSE_HPP__

namespace httpclient
{
    template<typename t_body>
    class http_response
    {
    private:
        t_body _body;

    public:
        http_response(t_body &&body = t_body())
            : _body(std::move(body))
        {
        }

        const t_body &body() const
        {
            return _body;
        }
    };
}

#endif // __HTTP_RESPONSE_HPP__
