cmake_minimum_required(VERSION 3.3)
project(homework2)
if (CMAKE_SYSTEM MATCHES "Linux")
    add_definitions(-D__Linux__)
endif()
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)
set(MESA_GL_VERSION_OVERRIDE "310")
set(MESA_GLSL_VERSION_OVERRIDE "310")
add_executable(homework2 Application.cpp libs/VertexArray.cpp libs/VertexBuffer.cpp libs/IndexBuffer.cpp libs/Shader.cpp libs/Texture.cpp libs/Renderer.cpp vendor/stb_image/stb_image.cpp libs/Transformation.cpp libs/Transformation.h)
target_link_libraries(homework2 glfw GLEW libGLEW.so libGLU.so libGL.so)

