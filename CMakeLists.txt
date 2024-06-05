cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
include_directories(/usr/local/include/box2d)

# Set policy to prefer GLVND
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()
set(OpenGL_GL_PREFERENCE GLVND)

set(SOURCES
    src/main.cpp
    src/window.cpp
    src/userInput.cpp
    src/rendering.cpp
    src/physics.cpp
    src/glad.c
    src/utilities.cpp
    src/shapeFactory.cpp
    src/circle.cpp
    src/edge.cpp
    src/graph.cpp
)

add_executable(main ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_COMPILER "g++")

target_link_libraries(main OpenGL::GL glfw box2d)

# Copy shaders to the binary directory
set(SHADERS
    shaders/vertex_shader_circle.glsl
    shaders/fragment_shader_circle.glsl
    shaders/vertex_shader_edge.glsl
    shaders/fragment_shader_edge.glsl
)

foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    configure_file(${SHADER} ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME} COPYONLY)
endforeach()

# Ensure the shaders directory exists in the build output
add_custom_target(copy_shaders ALL
    DEPENDS ${SHADERS}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SHADERS} ${CMAKE_BINARY_DIR}/shaders/
)
