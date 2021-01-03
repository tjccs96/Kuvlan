#include <set>
#include "vk_phys_device.h"

namespace kuvlan {

  vk_phys_device::vk_phys_device(const vk_instance* a_instance)
    : vkinstance_(a_instance)
  {
    init();
  }

  bool vk_phys_device::is_device_suitable(VkPhysicalDevice a_physical_device)
  {
    VkPhysicalDeviceProperties device_properties;
    VkPhysicalDeviceFeatures device_features;
    vkGetPhysicalDeviceProperties(a_physical_device, &device_properties);
    vkGetPhysicalDeviceFeatures(a_physical_device, &device_features);

    return device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
      device_features.geometryShader;
  }

  bool vk_phys_device::has_all_device_extensions(VkPhysicalDevice phy) const
  {
    // enumerate device extensions
    std::vector<VkExtensionProperties> exts;
    kuvlan::enumerate(phy, nullptr, exts);

    std::set<std::string> ext_names;
    for (const auto& ext :exts) {
      ext_names.insert(ext.extensionName);
    }

    // all listed device extensions are required
    for (const auto& name :device_extensions_) {
      if (ext_names.find(name) == ext_names.end())
        return false;
    }
    return true;
  }


  void vk_phys_device::init()
  {
    std::vector<VkPhysicalDevice> phys;
    kuvlan::assert_success(kuvlan::enumerate(vkinstance_->get_instance(), phys));


    for (auto phy :phys) {
      if (!has_all_device_extensions(phy)) {
        continue;
      }
      if (!is_device_suitable(phy)) {
        continue;
      }

      // get queue properties
      std::vector<VkQueueFamilyProperties> queues;
      kuvlan::get(phy, queues);

      //    int game_queue_family = -1, present_queue_family = -1;
      //    for (uint32_t i = 0; i < queues.size(); i++) {
      //        const VkQueueFamilyProperties& q = queues[i];

      //        // requires only GRAPHICS for game queues
      //        const VkFlags game_queue_flags = VK_QUEUE_GRAPHICS_BIT;
      //        if (game_queue_family < 0 && (q.queueFlags & game_queue_flags) == game_queue_flags) game_queue_family = i;

      //        // present queue must support the surface
      //        if (present_queue_family < 0 && can_present(phy, i)) present_queue_family = i;

      //        if (game_queue_family >= 0 && present_queue_family >= 0) break;
      //    }

      //    if (game_queue_family >= 0 && present_queue_family >= 0) {
      //        ctx_.physical_dev = phy;
      //        ctx_.game_queue_family = game_queue_family;
      //        ctx_.present_queue_family = present_queue_family;
      //        break;
      //    }
    }

    //if (ctx_.physical_dev == VK_NULL_HANDLE) throw std::runtime_error("failed to find any capable Vulkan physical device");
  }
}
