#ifndef __HTTP_FORM_BODY_HPP__
#define __HTTP_FORM_BODY_HPP__

#include <list>
#include <string>
#include <utility>

#include "http_body.hpp"

namespace httpclient
{
    using http_key_value = std::pair<std::string, std::string>;

    class http_form_body : public http_body
    {
    private:
        std::list<http_key_value> _values;

    public:
        void append(const std::string &key, const std::string &value);
    };
}

#endif // __HTTP_FORM_BODY_HPP__
