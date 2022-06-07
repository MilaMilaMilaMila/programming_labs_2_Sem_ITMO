cmake_minimum_required(VERSION 3.20)
project(kubikBubik)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(glew-cmake )
add_subdirectory(glfw)
add_executable(kubikBubik main.cpp lilCube.h Cube.h Friedrich.h interface.h programInterface.h glad/src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew-cmake/include PUBLIC glfw/include PUBLIC glad/include)
target_link_libraries(${PROJECT_NAME} libglew_static glfw)

