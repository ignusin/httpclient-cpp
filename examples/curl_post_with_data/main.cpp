#include <httpclient/httpclient.hpp>
#include <httpclient/curl/httpclient_curl.hpp>

#include <iostream>

namespace hc = httpclient;

int main()
{
    hc::curl::httpclient_curl_initializer curl_initializer;

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
}
