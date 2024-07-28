cmake_minimum_required(VERSION 3.16.0)
project(RDP VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

find_package(Vulkan REQUIRED)

include_directories(
  include
  externals/glfw/include
  externals/glm/
  shaders
)

set(SHADER_DIR ${PROJECT_ROOT_DIR}/shaders)
file(GLOB SHADERS ${SHADER_DIR}/*.vert ${SHADER_DIR}/*.frag)

foreach(SHADER IN LISTS SHADERS)
  get_filename_component(FILENAME ${SHADER} NAME)
  add_custom_command(OUTPUT ${SHADER_DIR}/${FILENAME}.spv
    COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER} -o ${SHADER_DIR}/${FILENAME}.spv
    DEPENDS ${SHADER}
    COMMENT "Compiling ${FILENAME}")

  list(APPEND SPV_SHADERS ${SHADER_DIR}/${FILENAME}.spv)
endForeach()
add_custom_target(shaders ALL DEPENDS ${SPV_SHADERS})

add_subdirectory(externals/glfw)
add_subdirectory(externals/glm)
add_subdirectory(sources)
