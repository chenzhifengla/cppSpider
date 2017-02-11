cmake_minimum_required(VERSION 3.6)
project(cppSpider)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES main.cpp Crawler.cpp HtmlParser.cpp Url.cpp Page.cpp)
set(SOURCE_FILES main.cpp Url.cpp Crawler.cpp Page.cpp)
add_executable(cppSpider ${SOURCE_FILES})