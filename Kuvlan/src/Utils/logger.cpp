#include "logger.h"

namespace kuvlan {

  std::shared_ptr<spdlog::logger> logger::core_logger_;
  std::shared_ptr<spdlog::logger> logger::client_logger_;

  void logger::init()
  {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    core_logger_ = spdlog::stdout_color_mt("Kuvlan");
    core_logger_->set_level(spdlog::level::trace);

    client_logger_ = spdlog::stdout_color_mt("App");
    client_logger_->set_level(spdlog::level::trace);
  }
} // namespace kuvlan
