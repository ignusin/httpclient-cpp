cmake_minimum_required(VERSION 3.8)

project(examples_curl_post_with_data)

# add_subdirectory(${CMAKE_SOURCE_DIR}/../../httpclient/curl httpclient_curl)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../httpclient httpclient)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../..)

link_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/httpclient_curl
    ${CMAKE_CURRENT_BINARY_DIR}/httpclient)

add_compile_options(-g)

add_executable(examples_curl_post_with_data
    main.cpp)

target_link_libraries(examples_curl_post_with_data
    httpclient_curl
    httpclient
    curl)
