#include "spxpch.h"
#include "Spixii/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Spixii
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_applicationLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_coreLogger = spdlog::stdout_color_mt("SPIXII");
		s_coreLogger->set_level(spdlog::level::trace);

		s_applicationLogger = spdlog::stdout_color_mt("APPLICATION");
		s_applicationLogger->set_level(spdlog::level::trace);
	}
}