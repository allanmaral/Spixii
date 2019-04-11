#pragma once

#include "Core.h"

namespace Spixii
{
	class SPIXII_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Needs to be defined in the client
	Application* CreateApplication();
}

