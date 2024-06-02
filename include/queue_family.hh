#ifndef __queue_family_hh__
#define __queue_family_hh__

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>
#include <stdexcept>
#include <iostream>

namespace Application {

class QueueFamilyIndices {
public:
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete();
private:
};

}

#endif
