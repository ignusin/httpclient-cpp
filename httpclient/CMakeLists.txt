cmake_minimum_required(VERSION 3.8)

project(httpclient)

add_library(httpclient
    chunked_buffer_reader.cpp
    http_form_body.cpp
    httpclient.cpp)
