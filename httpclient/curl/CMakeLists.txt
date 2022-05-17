cmake_minimum_required(VERSION 3.8)

project(httpclient_curl)

add_library(httpclient_curl
    httpclient_curl_initializer.cpp
    httpclient_curl_handle.cpp)
