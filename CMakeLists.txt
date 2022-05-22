cmake_minimum_required(VERSION 3.22)
project(untitled3)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)


add_executable(untitled3 main.cpp User.cpp User.h Data.cpp Data.h Transaction.cpp Transaction.h)

target_link_libraries(untitled3 /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
