#include "frpch.h"
#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Forge {

	FRef<spdlog::logger> Log::s_coreLogger;
	FRef<spdlog::logger> Log::s_clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("[%T] %n: %v%$");


		s_coreLogger = spdlog::stdout_color_mt("ForgeEngine");
		s_coreLogger->set_level(spdlog::level::trace);
		s_clientLogger = spdlog::stdout_color_mt("FEClient");
		s_clientLogger->set_level(spdlog::level::trace);
	}


}