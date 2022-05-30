#include <httpclient/httpclient.hpp>
#include <httpclient/curl/httpclient_curl.hpp>

#include <iostream>

namespace hc = httpclient;

int main()
{
    hc::curl::httpclient_curl_initializer curl_initializer;

    hc::http_headers headers;
    headers.append("X-Test-Header", "httpclient_cpp");

    hc::http_form_body form_body;
    form_body.append("field1", "value1");
    form_body.append("field2", "value2");

    hc::http_request<hc::http_form_body> request{
        hc::http_post,
        "https://httpbin.org/post",
        std::move(headers),
        std::move(form_body)};
    
    auto result = hc::http_perform<hc::http_form_body, hc::http_string_body>(request);

    if (result)
    {
        std::cout << "Status code: " << result->status_code().code() << std::endl;
        
        std::cout << "Headers: " << std::endl;
        for (auto key_it = result->headers().begin(); key_it != result->headers().end(); ++key_it)
        {
            std::cout << "\t" << std::get<0>(*key_it) << ":" << std::endl;
            
            const auto &values = std::get<1>(*key_it);
            for (auto val_it = values.begin(); val_it != values.end(); ++val_it)
            {
                std::cout << "\t\t" << *val_it << std::endl;
            }
        }
        
        std::cout << "Body: " << std::endl;
        std::cout << result->body().content() << std::endl;
    }
    else
    {
        std::cout << "Error: " << result.error() << std::endl;
    }
}
