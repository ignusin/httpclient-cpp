cmake_minimum_required(VERSION 3.8)

project(httpclient_curl)

add_compile_options(-g)

add_library(httpclient_curl
    httpclient_curl_initializer.cpp
    httpclient_curl_handle.cpp
    httpclient_curl.cpp)
