#include "spxpch.h"

#include "Spixii/Application.h"

#define BIND_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Spixii
{

    Application::Application()
    {
        Log::Init();
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_FUNCTION(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(m_running)
        {
            m_window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(OnWindowClose));

        SPX_TRACE_CORE("{0}", event.ToString());
    }

    bool Application::OnWindowClose(WindowCloseEvent &event)
    {
        m_running = false;
        return false;
    }

}  // namespace Spixii