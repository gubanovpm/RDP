#ifndef __application_hh__
#define __application_hh__

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <queue_family.hh>
#include <SwapChainSupportDetails.hh>
#include <Camera.hh>

#include <fstream>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <set>

namespace Application {

class application {
public:
  void run();
private:
  const static uint32_t WIDTH  = 800;
  const static uint32_t HEIGHT = 600;
  const static int MAX_FRAMES_IN_FLIGHT = 2;

  GLFWwindow *window = nullptr;
  VkInstance instance = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  Camera camera;

  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  std::vector<VkImageView> swapChainImageViews;
  std::vector<VkFramebuffer> swapChainFramebuffers;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  VkRenderPass renderPass;
  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;

  VkPipeline graphicsPipeline;
  VkPipelineLayout pipelineLayout;
  
  VkQueue graphicsQueue;
  VkQueue presentQueue;

  uint32_t currentFrame = 0;
  bool framebufferResized = false;

  const std::vector<const char *> deviceExtensions = { 
    VK_KHR_SWAPCHAIN_EXTENSION_NAME 
  };

  const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

  void initWindow(); 
  void initVulkan();
  void mainLoop();
  void cleanup();
  void drawFrame();
  
  void createInstance();
  void pickPhysicalDevice();
  void createLogicalDevice();
  void createSurface();
  void createSwapChain();
  void createImageViews();
  void createGraphicsPipeline();
  void createRenderPass();
  void createFramebuffers();
  void createCommandPool();
  void createCommandBuffer();
  void createSyncObjects();
  void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
  VkShaderModule createShaderModule(const std::vector<char> &);

  void recreateSwapChain();
  void cleanupSwapChain();

  bool checkValidationLayerSupport();
  bool isDeviceSuitable(VkPhysicalDevice);
  bool checkDeviceExtensionSupport(VkPhysicalDevice);
  std::vector<const char*> getRequiredExtensions();

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
  bool isDeviceSuitable(VkPhysicalDevice &);

  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>&);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>&);

  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&);
  static std::vector<char> readFile(const std::string&);
  static void framebufferResizeCallback(GLFWwindow*, int, int);
};

}

#endif
