cmake_minimum_required(VERSION 3.10)
set(CMAKE_VERBOSE_MAKEFILE ON)

# set project name
project(githubAction)

# set compile features
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/test)
add_subdirectory(lib/googletest)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)

enable_testing()
