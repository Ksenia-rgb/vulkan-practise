#ifndef HELLO_TRIANGLE_APP_HPP
#define HELLO_TRIANGLE_APP_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace triangle
{
  class HelloTriangleApp
  {
  public:
    void run();

  private:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    GLFWwindow* window;
    VkInstance instance;

    void initWindow();
    void createInstance();
    void printAvailableExtensions();
    void initVulkan();
    void mainLoop();
    void cleanUp();
  };
}

#endif
