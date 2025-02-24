#include <application.hh>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {
  Application::application app;

  try {
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
