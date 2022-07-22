cmake_minimum_required(VERSION 2.15)

project(main)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
  src/main.cpp
  src/objects/primitives/Texture.cpp
  
  libs/glad/glad.c
  
  libs/imgui/imgui.cpp
  libs/imgui/backends/imgui_impl_glfw.cpp
  libs/imgui/backends/imgui_impl_opengl3.cpp
  libs/imgui/imgui_draw.cpp
  libs/imgui/imgui_tables.cpp
  libs/imgui/imgui_widgets.cpp
  libs/imgui/imgui_demo.cpp)

include_directories(libs/include)
include_directories(libs/imgui)

add_compile_options(-g -Wall)

add_executable(main ${SOURCES})
target_link_libraries(main ${CMAKE_DL_LIBS})
target_link_libraries(main glfw)
