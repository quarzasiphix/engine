#pragma once
#include <common.hpp>
namespace engine {
	class ENGINE_API log {
	public:
		/// test comment
		static void init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLog() { return s_corelogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLog() { return s_clientlogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_corelogger;
		static std::shared_ptr<spdlog::logger> s_clientlogger;
	};
}


// core logger 
#define EN_CORE_TRACE(...) ::engine::log::getCoreLog()->trace(__VA_ARGS__)
#define EN_CORE_ERROR(...) ::engine::log::getCoreLog()->error(__VA_ARGS__)
#define EN_CORE_INFO(...)  ::engine::log::getCoreLog()->info(__VA_ARGS__)
#define EN_CORE_WARN(...)  ::engine::log::getCoreLog()->warn(__VA_ARGS__)
//#define EN_CORE_FATAL(...) ::engine::log::getCoreLog()->fatal(__VA_ARGS__)

// client logger
#define EN_TRACE(...) ::engine::log::getClientLog()->trace(__VA_ARGS__)
#define EN_ERROR(...) ::engine::log::getClientLog()->error(__VA_ARGS__)
#define EN_INFO(...)  ::engine::log::getClientLog()->info(__VA_ARGS__)
#define EN_WARN(...)  ::engine::log::getClientLog()->warn(__VA_ARGS__)
//#define EN_FATAL(...) ::engine::log::getClientLog()->fatal(__VA_ARGS__)
