cmake_minimum_required(VERSION 3.8)
project(multithread-game)

set(CMAKE_CXX STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-std=c++17")

set(JUST_INSTALL_CEREAL ON)
add_subdirectory(submodules/cereal)

add_subdirectory(src bin)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
    add_subdirectory(submodules/googletest)
endif()