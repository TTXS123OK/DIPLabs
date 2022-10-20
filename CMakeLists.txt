cmake_minimum_required(VERSION 3.22.1)
project(DIPLabs)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

#message(${EXECUTABLE_OUTPUT_PATH})
#message(${PROJECT_SOURCE_DIR})

add_executable(hello src/main.cpp)
#add_executable(DIPLabs ${PROJECT_SOURCE_DIR}/main.cpp)