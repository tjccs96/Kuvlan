#pragma once

#include <cstdint>
#include <string>
#include <memory>

namespace kuvlan {

  struct window_props
  {
    std::string title;
    uint32_t width;
    uint32_t height;

    window_props(const std::string& title = "Kuvlan Engine", uint32_t width = 1280, uint32_t height = 720)
      : title(title), width(width), height(height)
    {
    }
  };

  // Base window class
  class window
  {
  public:
    virtual ~window() = default;

    virtual void on_update() = 0;

    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_height() const = 0;

    // virtual void* get_native_window() const = 0;
    static std::unique_ptr<window> create(const window_props& props = window_props());

  };
}
