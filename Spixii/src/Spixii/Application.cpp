#include "spxpch.h"

#include "Spixii/Application.h"

#include "Spixii/Events/ApplicationEvent.h"
#include "Spixii/Log.h"
#include "Spixii/Window/Window.h"

namespace Spixii
{

    Application::Application()
    {
        Log::Init();
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        std::unique_ptr<Window> window = std::unique_ptr<Window>(Window::Create());

        while(true)
        {
            window->OnUpdate();
        }
    }

}  // namespace Spixii