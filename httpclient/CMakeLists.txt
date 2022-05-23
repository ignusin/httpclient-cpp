cmake_minimum_required(VERSION 3.8)

project(httpclient)

add_compile_options(-g)

add_library(httpclient
    chunked_buffer.cpp
    chunked_buffer_reader.cpp
    # http_byte_body.cpp
    http_form_body.cpp
    http_string_body.cpp
    http_body_conversions.cpp
    http_utility.cpp
    httpclient.cpp)
