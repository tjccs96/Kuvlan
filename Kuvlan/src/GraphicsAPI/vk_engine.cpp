#include "vk_engine.h"


namespace kuvlan {

  vk_engine::vk_engine()
  {
    init_vulkan();
    //init_swapchain();
  }

  vk_engine::~vk_engine()
  {
    cleanup();
  }

  VkResult vk_engine::create_debug_report()
  {
    PFN_create_debug_messenger = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(
      vk_ins_->get_instance(), "vkCreateDebugUtilsMessengerEXT"));

    if (!PFN_create_debug_messenger) {
      std::cout <<
        "Error: GetInstanceProcAddr unable to locate \
                    vkCreateDebugUtilsMessengerEXT function";
      return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Get vkDestroyDebugReportCallbackEXT API
    PFN_destroy_debug_messenger = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(
      vk_ins_->get_instance(), "vkDestroyDebugUtilsMessengerEXT"));

    if (!PFN_destroy_debug_messenger) {
      std::cout <<
        "Error: GetInstanceProcAddr unable to locate \
                    vkDestroyDebugUtilsMessengerEXT function";
      return VK_ERROR_INITIALIZATION_FAILED;
    }
  }


  void vk_engine::init_debug_report()
  {
    VkDebugUtilsMessengerCreateInfoEXT debug_report_info = {};
    debug_report_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_report_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debug_report_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_report_info.pfnUserCallback = debug_callback;


    kuvlan::assert_success(PFN_create_debug_messenger(vk_ins_->get_instance(), &debug_report_info, nullptr, &debug_report_));
  }

  void vk_engine::init_vulkan()
  {
    vk_ins_ = std::make_unique<vk_instance>();
    create_debug_report();
    init_debug_report();
    vk_phys_dev_ = std::make_unique<vk_phys_device>(vk_ins_.get());
  }

  void vk_engine::create_swapchain()
  {
  }

  void vk_engine::cleanup()
  {
    // #TODO Destroy device->surface->debugCallback->instance
    // vkDestroyDevice(vk_device_->get_device(), nullptr);
    // vkDestroySurfaceKHR(instance_, surface_, nullptr);
    PFN_destroy_debug_messenger(vk_ins_->get_instance(), debug_report_, nullptr);
    //vkDestroyInstance(vk_ins_->get_instance(), nullptr);
  }

} // namespace kuvlan
