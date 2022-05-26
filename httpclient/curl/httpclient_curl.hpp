#ifndef __HTTPCLIENT_CURL_HPP__
#define __HTTPCLIENT_CURL_HPP__

#include "httpclient_curl_initializer.hpp"
#include "httpclient_curl_handle.hpp"
#include "../chunked_buffer.hpp"
#include "../chunked_buffer_reader.hpp"
#include "../http_conversions.hpp"
#include "../http_request.hpp"
#include "../http_response.hpp"

namespace httpclient
{
    namespace curl
    {
        size_t __curl_read_buffer_callback(char *buffer, size_t size, size_t nitems, void *userdata);
        size_t __curl_write_buffer_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
        
        void __http_curl_request_write_body(httpclient_curl_handle &handle, chunked_buffer_reader &reader);
        void __http_curl_response_read_header(httpclient_curl_handle &handle, chunked_buffer &buffer);
        void __http_curl_response_read_body(httpclient_curl_handle &handle, chunked_buffer &buffer);

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
                __http_curl_request_write_body(handle, reader);
            }

            handle.setopt(CURLOPT_HEADER, 1L);

            chunked_buffer header_buffer;
            __http_curl_response_read_header(handle, header_buffer);

            chunked_buffer response_buffer;
            __http_curl_response_read_body(handle, response_buffer);

            curl_easy_perform(*handle);



            return http_response<t_resp_body>(make_body<t_resp_body>(response_buffer));
        }
    }
}

#endif // __HTTPCLIENT_CURL_HPP__
