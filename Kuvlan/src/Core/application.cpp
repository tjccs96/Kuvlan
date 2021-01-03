#include "application.h"

namespace kuvlan {

  application::application()
  {
      window_ = std::unique_ptr<window>(window::create());
  }

  application::~application()
  {
    
  }

  void application::run()
  {
      while (running_) {
          window_->on_update();
          
      }
      //window_->shutdown();
  }

  void application::close()
  {
      running_ = false;
  }

  
} // namespace kuvlan
