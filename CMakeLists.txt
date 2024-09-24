cmake_minimum_required(VERSION 3.0)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 11)

# Include GLAD and GLFW directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source Files
add_executable(main src/main.cpp src/glad.c src/Shader.cpp src/Shader.hpp src/shaders/vertex_shader.vs src/shaders/fragment_shader.fs)

# Link libraries
target_link_libraries(main glfw GL m)
