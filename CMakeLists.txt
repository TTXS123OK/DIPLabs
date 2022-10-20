cmake_minimum_required(VERSION 3.22.1)
project(DIPLabs)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

#message(${EXECUTABLE_OUTPUT_PATH})
#message(${PROJECT_SOURCE_DIR})

add_subdirectory(src/lib)

add_executable(lab1 src/lab1.cpp)
target_include_directories(lab1 PUBLIC ${PROJECT_SOURCE_DIR}/src/lib)
target_link_libraries(lab1 PUBLIC lib)

#add_executable(DIPLabs ${PROJECT_SOURCE_DIR}/main.cpp)