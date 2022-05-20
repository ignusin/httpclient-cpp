#ifndef __HTTP_FORM_BODY_HPP__
#define __HTTP_FORM_BODY_HPP__

#include <list>
#include <string>
#include <utility>

#include "chunked_buffer.hpp"

namespace httpclient
{
    using http_key_value = std::pair<std::string, std::string>;

    class http_form_body
    {
    private:
        std::list<http_key_value> _values;

    public:
        void append(const std::string &key, const std::string &value);

        std::list<http_key_value>::const_iterator values_begin() const;
        std::list<http_key_value>::const_iterator values_end() const;
    };
}

#endif // __HTTP_FORM_BODY_HPP__
