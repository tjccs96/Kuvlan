#pragma once

#include "vk_instance.h"
#include "vk_phys_device.h"
#include "../Utils/logger.h"

namespace kuvlan {

  class vk_engine
  {
  public:
    vk_engine();
    ~vk_engine();
    void cleanup();

    VkDebugUtilsMessengerEXT debug_report_;


  private:

    // static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                         VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                         const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                         void* pUserDat)
    {
      if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        KV_CORE_WARN(pCallbackData->pMessage, '\n');
      }
      else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        KV_CORE_INFO(pCallbackData->pMessage, '\n');
      }
      else {
        KV_CORE_ERROR(pCallbackData->pMessage, '\n');
      }
      return VK_FALSE;
    }

    PFN_vkCreateDebugUtilsMessengerEXT PFN_create_debug_messenger;
    PFN_vkDestroyDebugUtilsMessengerEXT PFN_destroy_debug_messenger;

    VkResult create_debug_report();
    void init_debug_report();

    bool validate_verbose_ = false;
    const static vk_engine* engine_instance_;
    std::unique_ptr<vk_instance> vk_ins_;
    std::unique_ptr<vk_phys_device> vk_phys_dev_;

    VkInstance instance_;
    VkDevice device_;

    void init_vulkan();
    void create_swapchain();
  };

} // namespace kuvlan
