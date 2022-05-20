#ifndef __HTTPCLIENT_HPP__
#define __HTTPCLIENT_HPP__

#define __HTTPCLIENT_IMPL_CURL

#include "http_request.hpp"
#include "http_response.hpp"
#include "http_byte_body.hpp"
#include "http_form_body.hpp"
#include "http_string_body.hpp"
#include "http_body_conversions.hpp"

#include <system_error>

#ifdef __HTTPCLIENT_IMPL_CURL
#include "curl/httpclient_curl.hpp"
#endif // __HTTPCLIENT_IMPL_CURL

namespace httpclient
{
    template<typename t_req_body, typename t_resp_body>
    http_response<t_resp_body> http_perform(
        const http_request<t_req_body> &request)
    {
#ifdef __HTTPCLIENT_IMPL_CURL
        return curl::http_curl_perform<t_req_body, t_resp_body>(request);
#endif // __HTTPCLIENT_IMPL_CURL
    }
}

#endif // __HTTPCLIENT_HPP__
