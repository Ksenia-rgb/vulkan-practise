#ifndef HELLO_TRIANGLE_APP_HPP
#define HELLO_TRIANGLE_APP_HPP

#define VK_USE_PLATFORM_WIN32_KHR

#define NOMINMAX
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>

#include <vector>
#include <optional>
#include <string>

namespace triangle
{
  struct QueueFamilyIndices
  {
    std::optional< uint32_t > graphicsFamily;
    std::optional< uint32_t > presentFamily;

    bool isComplete();
  };

  struct SwapChainSupportDetails
  {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector< VkSurfaceFormatKHR > formats;
    std::vector< VkPresentModeKHR > presentModes;
  };

  struct Vertex
  {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array< VkVertexInputAttributeDescription, 2 > getAttributeDescriptions();
  };

  class HelloTriangleApp
  {
  public:
    void run();

  private:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    const std::vector< const char* > validationLayers = { "VK_LAYER_KHRONOS_validation" };
    const std::vector< const char* > deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    const int MAX_FRAMES_IN_FLIAGHT = 2;

    const std::vector< Vertex > vertices = {
      { {-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      { {0.5f, -0.5f}, {0.0f, 1.0f, 0.0f} },
      { {0.5f, 0.5f}, {0.0f, 0.0f, 1.0f} },
      { {-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f} }
    };

    const std::vector< uint16_t > indices = { 0, 1, 2, 2, 3, 0 };

    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessanger;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector< VkImage > swapChainImages;
    std::vector< VkImageView > swapChainImageViews;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector< VkFramebuffer > swapChainFramebuffers;
    VkCommandPool commandPool;
    std::vector< VkCommandBuffer > commandBuffers;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector< VkSemaphore > imageAvailableSemaphores;
    std::vector< VkSemaphore >renderFinishedSemaphores;
    std::vector< VkFence > inFlightFences;

    bool framebufferResized = false;

    uint32_t currentFrame = 0;

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    void createInstance();
    void setupDebugMessenger();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffer();
    void createSyncObjects();
    void recreateSwapChain();
    void createVertexBuffer();
    void createIndexBuffer();

    void printAvailableExtensions();
    bool checkValidationLayerSupport();
    std::vector< const char* > getRequiredExtensions();

    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector< VkSurfaceFormatKHR >& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector< VkPresentModeKHR >& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    VkShaderModule createShaderModule(const std::vector< char >& code);

    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void drawFrame();

    void cleanupSwapChain();

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
      VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
  };

  VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
  );

  VkResult createDebugUtilsMessengerEXT(VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger
  );

  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

  void destroyDebugUtilsMessengerEXT(VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator
  );

  int rateDeviceSuitability(VkPhysicalDevice device);

  std::vector< char > readByteFile(const std::string& filename);
}

#endif
