cmake_minimum_required(VERSION 2.8.0)

PROJECT(vector)
set(BINNAME vector)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    )
SET(SRC main.cpp
        )

SET(HDR vector.hpp
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ADD_EXECUTABLE(${BINNAME} ${SRC} ${HDR})
