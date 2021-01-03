#pragma once

#include <memory>
#include "window.h"


namespace kuvlan {


  class application
  {
  public:
	  application();
	  virtual ~application();

	  void run();
	  void close();

  private:
	  std::unique_ptr<window> window_;
	  bool running_ = true;
	  //friend int ::main(int argc, char** argv);
	};

  application* create_application();

}

