#pragma once

#include <memory.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace kuvlan {

  class logger
	{
  public:
	  static void init();

	  inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return core_logger_; }
	  inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return client_logger_; }

  private:
	  static std::shared_ptr<spdlog::logger> core_logger_;
	  static std::shared_ptr<spdlog::logger> client_logger_; // For later use.
	};

}

// Log macros
#define KV_CORE_FATAL(...) ::kuvlan::logger::get_core_logger()->critical(__VA_ARGS__)
#define KV_CORE_ERROR(...) ::kuvlan::logger::get_core_logger()->error(__VA_ARGS__)
#define KV_CORE_WARN(...)  ::kuvlan::logger::get_core_logger()->warn(__VA_ARGS__)
#define KV_CORE_INFO(...)  ::kuvlan::logger::get_core_logger()->info(__VA_ARGS__)
#define KV_CORE_TRACE(...) ::kuvlan::logger::get_core_logger()->trace(__VA_ARGS__)