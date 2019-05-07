#include "spxpch.h"

#include "Spixii/Application.h"
#include "Spixii/Base/Platform/LibraryLoader.h"
#include "Spixii/Base/Engine.h"
#include "Spixii/Events/ApplicationEvent.h"
#include "Spixii/Events/KeyEvent.h"
#include "Spixii/Events/MouseEvent.h"
#include "Spixii/Log.h"
#include "Spixii/Window/Window.h"

namespace Spixii
{
    Allocator *        Engine::s_globalAllocator = nullptr;
    Window *           Engine::s_window          = nullptr;
    bool               Engine::s_isRunning       = false;
    ApplicationSystems Engine::s_application     = {};
    char               g_staticBuffer[SPX_MAX_BUFFER_SIZE];

    typedef int(__cdecl *f_handShakeFn)(Spixii::SpixiiSystems *sys, Spixii::ApplicationSystems *app);
    typedef int(__cdecl *f_shutdownFn)();

    void Engine::Initialize()
    {
        // Initialize most of the engine sub-systems
        Log::Initialize();
        // TODO: File system
        s_window = Window::Create();  // Properties should be read from file config (IMPLEMENT .INI maybe)
        s_window->SetEventCallback(Engine::OnEvent);

        // Load application and exchange data
        s_application.sharedLibrary = LibraryLoader::LoadSharedLibrary(L"Sandbox.dll");
        f_handShakeFn handShakeFn   = (f_handShakeFn)LibraryLoader::GetProcedure(s_application.sharedLibrary,
                                                                               "HandShake");
        SpixiiSystems sistemView = GetSystemView();
        int result = handShakeFn(&sistemView, &s_application);
        SPX_ASSERT_CORE(result, "Could handshake shared library");

        s_application.application->Initialize();
    }

    void Engine::Shutdown()
    {
        s_window->Shutdown();
        delete s_window;  // TODO: Remove new and deletes

        f_shutdownFn shutdownFn = (f_shutdownFn)LibraryLoader::GetProcedure(s_application.sharedLibrary,
                                                                            "Shutdown");
        shutdownFn();
        LibraryLoader::ReleaseLibrary(s_application.sharedLibrary);
    }

    void Engine::Update()
    {
        s_window->OnUpdate();
        s_application.application->OnUpdate();
    }

    void Engine::OnEvent(Spixii::Event &event)
    {
        if(event.GetEventType() == Spixii::WindowCloseEvent::GetStaticType())
        {
            s_isRunning = false;
            return;
        }
        // Filter or process important events before passing to the application
        if(s_application.application)
        {
            s_application.application->OnEvent(event);
        }

        SPX_TRACE_CORE("OnEvent: {0}", event.ToString());
    }

    SpixiiSystems Engine::GetSystemView()
    {
        SpixiiSystems systemView   = {};
        systemView.version         = SPIXII_VERSION;
        systemView.globalAllocator = s_globalAllocator;
        systemView.window          = s_window;
        systemView.isRunning       = &s_isRunning;
        return systemView;
    }

}  // namespace Spixii