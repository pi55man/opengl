cmake_minimum_required(VERSION 3.0)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 11)

# Include GLAD and GLFW directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source Files
add_executable(main src/main.cpp src/glad.c)

# Link libraries
target_link_libraries(main glfw GL m)
