#include <httpclient/httpclient.hpp>
#include <httpclient/curl/httpclient_curl.hpp>

#include <iostream>
#include <system_error>

namespace hc = httpclient;

int main()
{
    hc::curl::httpclient_curl_initializer curl_initializer;

    hc::http_form_body form_body;
    form_body.append("field1", "value1");
    form_body.append("field2", "value2");

    hc::http_request<hc::http_form_body> request{
        hc::http_post,
        "https://httpbin.org/post",
        std::move(form_body)};
    
    auto resp = hc::http_perform<hc::http_form_body, hc::http_string_body>(request);
    
    std::cout << resp.body().content() << std::endl;

    /*
    hc::curl::httpclient_curl_handle curl;
    if (!curl)
    {
        std::cout << "Could not inialize CURL" << std::endl;
        return 0;
    }

    curl.setopt(CURLOPT_URL, "https://httpbin.org/post");
    curl.setopt(CURLOPT_POSTFIELDS, "field1=value1&field2=value2");

    const auto res = curl_easy_perform(*curl);
    if (res != CURLE_OK)
    {
        std::cout << "Error while sending request" << std::endl;
    }
    */
}
