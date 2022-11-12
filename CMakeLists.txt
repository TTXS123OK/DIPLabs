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

add_executable(lab2 src/lab2.cpp)
target_include_directories(lab2 PUBLIC ${PROJECT_SOURCE_DIR}/src/lib)
target_link_libraries(lab2 PUBLIC lib)

add_executable(lab3 src/lab3.cpp)
target_include_directories(lab3 PUBLIC ${PROJECT_SOURCE_DIR}/src/lib)
target_link_libraries(lab3 PUBLIC lib)

add_executable(lab4 src/lab4.cpp)
target_include_directories(lab4 PUBLIC ${PROJECT_SOURCE_DIR}/src/lib)
target_link_libraries(lab4 PUBLIC lib)