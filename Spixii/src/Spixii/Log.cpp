#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Spixii
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ApplicationLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger   = spdlog::stdout_color_mt("Spixii");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ApplicationLogger = spdlog::stdout_color_mt("Application");
		s_ApplicationLogger->set_level(spdlog::level::trace);
	}
}