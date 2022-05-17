#ifndef __HTTPCLIENT_CURL_HANDLE_HPP__
#define __HTTPCLIENT_CURL_HANDLE_HPP__

#include <curl/curl.h>

namespace httpclient
{
    namespace curl
    {

        class httpclient_curl_handle
        {
        private:
            CURL* _handle = nullptr;

        public:
            httpclient_curl_handle();
            ~httpclient_curl_handle();

            CURL* handle() const;
            CURL* operator*() const;

            operator bool() const;

            template<class ... Args>
            CURLcode setopt(CURLoption option, Args ... args)
            {
                return curl_easy_setopt(handle(), option, args...);
            }
        };

    }
}

#endif // __HTTPCLIENT_CURL_HANDLE_HPP__
