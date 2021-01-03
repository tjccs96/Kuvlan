#include "win_window.h"
#include "../Utils/logger.h"

namespace kuvlan {

  win_window::win_window(const window_props& props)
  {
      init(props);
  }

  std::unique_ptr<window> window::create(const window_props& props)
  {
    //return new win_window(props);
    return std::make_unique<win_window>(props);
  }

  

  win_window::~win_window()
  {
      shutdown();
  }

  void win_window::init(const window_props& props)
  {
      data_.title = props.title;
      data_.width = props.width;
      data_.height = props.height;

      glfwInit();

      if (glfwVulkanSupported())
      {
          KV_CORE_WARN("Vulkan is supported");
      }

      KV_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

      glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
      window_ = glfwCreateWindow((int)props.width, (int)props.height, data_.title.c_str(), nullptr, nullptr);
      glfwMakeContextCurrent(window_);
      glfwSetWindowUserPointer(window_, &data_);
  }

  void win_window::shutdown()
  {
      glfwDestroyWindow(window_);
      glfwTerminate();
  }

  void win_window::on_update()
  {
      glfwPollEvents();
      glfwSwapBuffers(window_);
  }
}
