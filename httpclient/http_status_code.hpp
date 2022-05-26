#ifndef __HTTP_STATUS_CODE_HPP__
#define __HTTP_STATUS_CODE_HPP__

#include <string>

namespace httpclient
{
    class http_status_code
    {
    private:
        unsigned int _code;
        std::string _text;
    public:
        http_status_code(const unsigned int code, const std::string &text);

        unsigned int code() const;
        const std::string &text() const; 
    };
}

#endif // __HTTP_STATUS_CODE_HPP__
