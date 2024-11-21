cmake_minimum_required(VERSION 3.29)
project(Builder)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

add_executable(Builder main.cpp)

target_link_libraries(Builder OpenSSL::SSL OpenSSL::Crypto)

include_directories(/path/to/openssl/include)
link_directories(/path/to/openssl/lib)