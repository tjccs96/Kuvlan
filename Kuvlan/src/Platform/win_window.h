#pragma once

#include "../Core/window.h"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

namespace kuvlan {


	class win_window : public window
	{

	public:
	  win_window(const window_props& props);
	  virtual ~win_window();

	  GLFWwindow* get_window() const { return window_; }

	  inline unsigned int get_width() const override { return data_.width; }
	  inline unsigned int get_height() const override { return data_.height; }

	  void on_update() override;

	private:
		virtual void init(const window_props& props);
		virtual void shutdown();
	
		GLFWwindow* window_;

    struct window_data
    {
		  std::string title;
		  unsigned int width;
		  unsigned int height;
    };

	  window_data data_;
	};

} // namespace kuvlan