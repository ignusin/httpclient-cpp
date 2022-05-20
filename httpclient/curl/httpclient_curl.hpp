#ifndef __HTTPCLIENT_CURL_HPP__
#define __HTTPCLIENT_CURL_HPP__

#include "httpclient_curl_initializer.hpp"
#include "httpclient_curl_handle.hpp"
#include "../chunked_buffer.hpp"
#include "../chunked_buffer_reader.hpp"
#include "../http_body_conversions.hpp"

namespace httpclient
{
    namespace curl
    {
        template<typename t_req_body>
        void __http_curl_request_set_verb(
            httpclient_curl_handle &handle,
            const http_request<t_req_body> &request)
        {
            if (request.verb() == http_verb::http_post)
            {
                handle.setopt(CURLOPT_POST, 1L);
            }
            else
            {
                handle.setopt(CURLOPT_HTTPGET, 1L);
            }
        }

        template<typename t_req_body>
        void __http_curl_request_set_url(
            httpclient_curl_handle &handle,
            const http_request<t_req_body> &request)
        {
            handle.setopt(CURLOPT_URL, request.url().c_str());
        }

        inline size_t __curl_read_callback(
            char *buffer, size_t size, size_t nitems, void *userdata)
        {
            chunked_buffer_reader &reader = *static_cast<chunked_buffer_reader*>(userdata);
            auto result = reader.read(reinterpret_cast<uint8_t *>(buffer), size * nitems);
        
            return result;
        }

        template<typename t_req_body>
        void __http_curl_request_write_body(
            httpclient_curl_handle &handle,
            const http_request<t_req_body> &request,
            chunked_buffer_reader &reader)
        {
            handle.setopt(CURLOPT_READFUNCTION, __curl_read_callback);
            handle.setopt(CURLOPT_READDATA, &reader);
        }

        template<typename t_req_body>
        void __http_curl_request_prepare(
            httpclient_curl_handle &handle,
            const http_request<t_req_body> &request)
        {
            __http_curl_request_set_verb(handle, request);
            __http_curl_request_set_url(handle, request);
        }

        template<typename t_req_body, typename t_resp_body>
        http_response<t_resp_body> http_curl_perform(
            const http_request<t_req_body> &request)
        {
            chunked_buffer buffer = make_buffer(request.body());
            chunked_buffer_reader reader(buffer);

            httpclient_curl_handle handle;
            __http_curl_request_prepare(handle, request);

            if (request.verb() == http_post)
            {
                __http_curl_request_write_body(handle, request, reader);
            }

            curl_easy_perform(*handle);

            return http_response<t_resp_body>();
        }
    }
}

#endif // __HTTPCLIENT_CURL_HPP__
