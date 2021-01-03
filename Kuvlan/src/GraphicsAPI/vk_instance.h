#pragma once


#include <iostream>
#include <vulkan.hpp>
#include <vector>

#include "vk_helpers.h"
#include "../Utils/defines.h"

namespace kuvlan {

  class vk_instance
  {
  public:
    vk_instance();
    ~vk_instance();


    [[nodiscard]] FORCEINLINE const VkInstance& get_instance() const { return instance_; }

    // static const std::vector<const char*> validation_layers;

  private:

    VkInstance instance_ = VK_NULL_HANDLE;
    std::vector<const char*> instance_layers_;
    // std::vector<const char*> instance_extensions_;

    void assert_all_instance_layers() const;
    void assert_all_instance_extensions(std::vector<const char*> instance_extensions) const;

    // std::vector<const char*> get_extensions() const;

    void init_instance();
  };

}
