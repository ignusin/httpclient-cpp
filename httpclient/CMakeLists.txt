cmake_minimum_required(VERSION 3.8)

project(httpclient)

add_library(httpclient
    http_form_body.cpp
    httpclient.cpp)
