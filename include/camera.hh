#ifndef __Camera_hh__
#define __Camera_hh__

#include <vk_types.h>
#include <glm/glm.hpp>

namespace application {

class Camera final {
public:
  glm::vec3 velocity;
  glm::vec3 position;
  
  float pitch = 0.f;
  float yaw = 0.f;

  glm::mat4 getViewMatrix();
  glm::mat4 getRotationMatrix();

  // void processEvent();
  void update();
private:

};

}

#endif
