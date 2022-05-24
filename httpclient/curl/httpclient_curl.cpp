#include "httpclient_curl.hpp"

namespace hc = httpclient;


size_t hc::curl::__curl_read_buffer_callback(
    char *buffer, size_t size, size_t nitems, void *userdata)
{
    hc::chunked_buffer_reader &reader = *static_cast<hc::chunked_buffer_reader*>(userdata);
    auto result = reader.read(reinterpret_cast<uint8_t *>(buffer), size * nitems);

    return result;
}

size_t hc::curl::__curl_write_buffer_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    hc::chunked_buffer &buffer = *static_cast<hc::chunked_buffer*>(userdata);
    buffer.append(hc::chunked_buffer::chunk(reinterpret_cast<uint8_t *>(ptr), size * nmemb));

    return size * nmemb;
}

void hc::curl::__http_curl_request_write_body(
    hc::curl::httpclient_curl_handle &handle,
    hc::chunked_buffer_reader &reader)
{
    handle.setopt(CURLOPT_READFUNCTION, hc::curl::__curl_read_buffer_callback);
    handle.setopt(CURLOPT_READDATA, &reader);
}

void hc::curl::__http_curl_response_read_header(
    hc::curl::httpclient_curl_handle &handle,
    hc::chunked_buffer &buffer)
{
    handle.setopt(CURLOPT_HEADERFUNCTION, hc::curl::__curl_write_buffer_callback);
    handle.setopt(CURLOPT_HEADERDATA, &buffer);
}

void hc::curl::__http_curl_response_read_body(
    hc::curl::httpclient_curl_handle &handle,
    hc::chunked_buffer &buffer)
{
    handle.setopt(CURLOPT_WRITEFUNCTION, hc::curl::__curl_write_buffer_callback);
    handle.setopt(CURLOPT_WRITEDATA, &buffer);
}
