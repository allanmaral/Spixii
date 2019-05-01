#include "spxpch.h"
#include "Spixii/Application.h"

#include "Spixii/Log.h"
#include "Spixii/Events/ApplicationEvent.h"

namespace Spixii
{

	Application::Application()
	{
	}


	Application::~Application()
	{
	}


	void Application::Run()
	{
		Log::Init();

		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			SPX_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			SPX_ERROR(e);
		}

		while (true);
	}

}