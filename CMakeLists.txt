project(SPD_4)

cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run 
	PROJECT/code/main.cpp
	PROJECT/code/src/carlier.cpp
	PROJECT/code/src/proces.cpp)
add_executable(run_ut
	PROJECT/tests/test.cpp
	PROJECT/tests/src/ut_prmtS.cpp
	PROJECT/code/src/carlier.cpp
	PROJECT/code/src/proces.cpp)
target_link_libraries(run_ut gtest gtest_main pthread)
