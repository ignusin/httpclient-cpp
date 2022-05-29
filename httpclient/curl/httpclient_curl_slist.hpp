#ifndef __HTTPCLIENT_CURL_SLIST_HPP__
#define __HTTPCLIENT_CURL_SLIST_HPP__

#include <curl/curl.h>

#include <list>
#include <string>

namespace httpclient
{
    namespace curl
    {
        class httpclient_curl_slist
        {
        private:
            curl_slist *_list = nullptr;

        public:
            ~httpclient_curl_slist();

            void append(const std::string &name, const std::string &value);
            const curl_slist *list() const;
        };
    }
}

#endif // __HTTPCLIENT_CURL_SLIST_HPP__
