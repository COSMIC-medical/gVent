set(BINARY ${CMAKE_PROJECT_NAME}_test)
set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB TEST_SOURCES LIST_DIRECTORIES true *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest stdc++fs ${Boost_LIBRARIES})
