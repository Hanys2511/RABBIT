project(SPD_4)

cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(.)

file(GLOB code_SRC
    "PROJECT/code/src/*.cpp"
)

file(GLOB test_SRC
    "PROJECT/tests/src/*.cpp"
)

add_executable(run 
	PROJECT/code/main.cpp
	${code_SRC})

add_executable(run_ut
	PROJECT/tests/test.cpp
	${test_SRC}
	${code_SRC})

target_link_libraries(run_ut gtest gtest_main pthread)
