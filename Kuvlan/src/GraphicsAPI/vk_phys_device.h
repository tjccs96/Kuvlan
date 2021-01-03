#pragma once

#include <vulkan.hpp>
#include "vk_helpers.h"
#include "vk_instance.h"

namespace kuvlan {
  // class vk_instance;


  class vk_phys_device
	{
	public:
		vk_phys_device(const vk_instance* instance);

		[[nodiscard]]
		inline const VkPhysicalDevice& get_phy_device() const { return physical_device_; }

  private:
		const vk_instance* vkinstance_;
		VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
		std::vector<const char*> device_extensions_;

		bool is_device_suitable(VkPhysicalDevice a_physical_device);
		bool has_all_device_extensions(VkPhysicalDevice phy) const;
    void init();
	};

}
