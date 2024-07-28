set(EXEC rdp)

add_executable(${EXEC} 
  main.cc
  camera.cc
  application.cc
  queue_family.cc
)
target_link_libraries(${EXEC} 
  glfw 
  Vulkan::Vulkan
  glm
)
add_dependencies(${EXEC} shaders)

