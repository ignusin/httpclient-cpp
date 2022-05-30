cmake_minimum_required(VERSION 3.8)

project(httpclient)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/curl httpclient_curl)

add_compile_options(-g)

add_library(httpclient
    chunked_buffer.cpp
    chunked_buffer_reader.cpp
    # http_byte_body.cpp
    http_form_body.cpp
    http_string_body.cpp
    http_conversions.cpp
    http_utility.cpp
    http_headers.cpp
    http_status_code.cpp
    httpclient.cpp)
