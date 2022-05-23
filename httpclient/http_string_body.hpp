#ifndef __HTTP_STRING_BODY_HPP__
#define __HTTP_STRING_BODY_HPP__

#include <string>

namespace httpclient
{
    class http_string_body
    {
    private:
        std::string _content;

    public:
        http_string_body(std::string &&content);
        const std::string &content() const;
    };
}

#endif // __HTTP_STRING_BODY_HPP__
