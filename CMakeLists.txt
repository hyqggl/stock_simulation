cmake_minimum_required(VERSION 3.6)
project(stock_simulation)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        marketOrderGenerator.cpp
        marketOrderGenerator.h
        market.cpp
        market.h
        orderProcessor.cpp
        orderProcessor.h)
add_executable(stock_simulation ${SOURCE_FILES})