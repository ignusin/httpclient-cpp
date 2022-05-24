#ifndef __HTTP_HEADERS_HPP__
#define __HTTP_HEADERS_HPP__

#include <list>
#include <map>
#include <string>

namespace httpclient
{
    using http_header_values = std::map<std::string, std::list<std::string>>;

    class http_headers
    {
    private:
        http_header_values _values;
    public:
        void append(const std::string &key, const std::string &value);

        http_header_values::const_iterator begin() const;
        http_header_values::const_iterator end() const;
    };
}

#endif // __HTTP_HEADERS_HPP__
