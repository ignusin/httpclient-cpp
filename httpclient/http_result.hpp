#ifndef __HTTP_RESULT_HPP__
#define __HTTP_RESULT_HPP__

#include <memory>
#include "http_response.hpp"

namespace httpclient
{
    template<typename t_body>
    class http_result
    {
    private:
        std::unique_ptr<http_response<t_body>> _response;
        std::string _error;

    public:
        http_result(http_response<t_body> &&resp)
            : _response(new http_response<t_body>(std::move(resp))), _error()
        {
        }

        http_result(const std::string &error)
            : _response(), _error(error)
        {
        }

        operator bool() const
        {
            return !!_response;
        }

        const http_response<t_body> &operator*() const
        {
            return *_response;
        }

        const http_response<t_body> *operator->() const
        {
            return _response.get();
        }

        const std::string &error() const
        {
            return _error;
        }
    };
}

#endif // __HTTP_RESULT_HPP__
