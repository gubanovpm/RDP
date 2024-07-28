#include <camera.hh>

namespace Application {

void Camera::upadte() {
  glm::mat4 cameraRotation = getRotationMatrix();
  position += glm::vec3(cameraRotation * glm::vec4(velocity * 0.5f, 0.f));
}

void Camera::processEvent() {

}

}
