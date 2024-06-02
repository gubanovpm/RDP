set(EXEC rdp)

add_executable(${EXEC} 
  main.cc
  application.cc
  queue_family.cc
)
target_link_libraries(${EXEC} glfw Vulkan::Vulkan)
add_dependencies(${EXEC} shaders)

