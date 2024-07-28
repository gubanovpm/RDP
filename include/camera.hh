#ifndef __Camera_hh__
#define __Camera_hh__


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Application {

class Camera final {
public:
  glm::vec3 velocity;
  glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
  
  float pitch = 0.f;
  float yaw = 0.f;

  glm::mat4 getViewMatrix();
  glm::mat4 getRotationMatrix();

  static void key_callback(GLFWwindow *, const int, const int, const int, const int);
  void update();
private:
};

}

#endif
