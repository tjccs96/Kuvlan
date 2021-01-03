#include "vk_instance.h"
#include <glfw3.h>
#include <set>

#include "../Utils/logger.h"

namespace kuvlan {


  vk_instance::vk_instance()
  {
    init_instance();
  }

  vk_instance::~vk_instance()
  {
    vkDestroyInstance(instance_, nullptr);
  }

  void vk_instance::assert_all_instance_layers() const
  {
    // enumerate instance layer
    std::vector<VkLayerProperties> layers;
    kuvlan::enumerate(layers);

    std::set<std::string> layer_names;
    for (const auto& layer :layers) layer_names.insert(layer.layerName);

    // all listed instance layers are required
    for (const auto& name :instance_layers_) {
      if (layer_names.find(name) == layer_names.end()) {
        std::stringstream ss;
        ss << "instance layer " << name << " is missing";
        throw std::runtime_error(ss.str());
      }
    }
  }

  void vk_instance::assert_all_instance_extensions(std::vector<const char*> instance_extensions) const
  {
    // enumerate instance extensions
    // #TODO better way to pass this argument
    std::vector<VkExtensionProperties> exts;
    kuvlan::enumerate(nullptr, exts);

    std::set<std::string> ext_names;
    for (const auto& ext :exts) ext_names.insert(ext.extensionName);

    for (auto& layer :instance_layers_) {
      kuvlan::enumerate(layer, exts);
      for (const auto& ext :exts) ext_names.insert(ext.extensionName);
    }

    // all listed instance extensions are required
    for (const auto& name :instance_extensions) {
      if (ext_names.find(name) == ext_names.end()) {
        std::stringstream ss;
        ss << "instance extension " << name << " is missing";
        throw std::runtime_error(ss.str());
      }
    }
  }

  void vk_instance::init_instance()
  {
    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    instance_layers_.push_back("VK_LAYER_LUNARG_standard_validation");
    std::vector<const char*> instance_extensions_(glfw_extensions, glfw_extensions + glfw_extension_count);

#ifdef _DEBUG
    instance_extensions_.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    instance_extensions_.push_back("VK_EXT_debug_report");
    assert_all_instance_layers();
    assert_all_instance_extensions(instance_extensions_);
#endif

    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Kuvlan engine";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Kuvlan";
    app_info.engineVersion = VK_MAKE_VERSION(1, 2, 0);
    app_info.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo instance_info{};
    instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_info.pApplicationInfo = &app_info;
    instance_info.enabledLayerCount = static_cast<uint32_t>(instance_layers_.size());
    instance_info.ppEnabledLayerNames = instance_layers_.data();
    instance_info.enabledExtensionCount = static_cast<uint32_t>(instance_extensions_.size());
    instance_info.ppEnabledExtensionNames = instance_extensions_.data();

    // kuvlan::assert_success(vk::createInstance(instance_info, nullptr, instance_));
    kuvlan::assert_success(vkCreateInstance(&instance_info, nullptr, &instance_));
  }
}
