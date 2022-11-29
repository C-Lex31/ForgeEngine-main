#pragma once

#include "core/core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace Forge {

	class FORGE_API Log
	{
	public:
		static void Init();
		inline static FRef<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static FRef<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
	private:
		static FRef<spdlog::logger>s_coreLogger;
		static FRef<spdlog::logger>s_clientLogger;

	};


}

#define FR_CORE_TRACE(...)  ::Forge::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FR_CORE_INFO(...)   ::Forge::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FR_CORE_WARN(...)   ::Forge::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FR_CORE_ERROR(...)  ::Forge::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FR_CORE_FATAL(...)  ::Forge::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define FR_TRACE(...)  ::Forge::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FR_INFO(...)   ::Forge::Log::GetClientLogger()->info(__VA_ARGS__)
#define FR_WARN(...)   ::Forge::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FR_ERROR(...)  ::Forge::Log::GetClientLogger()->error(__VA_ARGS__)
#define FR_FATAL(...)  ::Forge::Log::GetClientLogger()->fatal(__VA_ARGS__)