#include "log.hpp"

namespace engine {
	std::shared_ptr<spdlog::logger> log::s_corelogger;
	std::shared_ptr<spdlog::logger> log::s_clientlogger;

	void log::init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_corelogger = spdlog::stdout_color_mt("ENGINE");
		s_corelogger->set_level(spdlog::level::trace);
	
		s_clientlogger = spdlog::stdout_color_mt("APP");
		s_clientlogger->set_level(spdlog::level::trace);
	}
}