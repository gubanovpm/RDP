#include <Camera.hh>

#include <iostream>

namespace Application {

void Camera::update() {
  glm::mat4 cameraRotation = getRotationMatrix();
  position += glm::vec3(cameraRotation * glm::vec4(velocity * 0.5f, 0.f));
}

void Camera::key_callback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_W : {
        // position += glm::vec3(0.f, 0.f, 0.25f);
        std::cout << "W key pressed" << std::endl;
        break;
      }
      case GLFW_KEY_S : {
        // position -= glm::vec3(0.f, 0.f, 0.25f);
        std::cout << "S key pressed" << std::endl;
        break;
      }
      case GLFW_KEY_A : {
        std::cout << "A key pressed" << std::endl;

        break;
      }
      case GLFW_KEY_D : {
        std::cout << "D key pressed" << std::endl;

        break;
      }
      case GLFW_KEY_Q: {
        std::cout << "Q key pressed" << std::endl;

        break;
      }
      case GLFW_KEY_E: {
        std::cout << "E key pressed" << std::endl;

        break;
      }
      case GLFW_KEY_R: {
        std::cout << "R key pressed" << std::endl;

        break;
      }
      case GLFW_KEY_F: {
        std::cout << "F key pressed" << std::endl;

        break;
      }
    }
    // update();
  }
}

glm::mat4 Camera::getViewMatrix() {
  glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.f), position);
  glm::mat4 cameraRotation = getRotationMatrix();
  return glm::inverse(cameraTranslation * cameraRotation);
}

glm::mat4 Camera::getRotationMatrix() {
  glm::quat pitchRotation = glm::angleAxis(pitch, glm::vec3 { 1.f, 0.f, 0.f });
  glm::quat yawRotation = glm::angleAxis(yaw, glm::vec3 { 0.f, -1.f, 0.f });

  return glm::toMat4(yawRotation) * glm::toMat4(pitchRotation);
}

}
