#pragma once

#include "spxpch.h"

#include "Spixii.h"



typedef int(__cdecl *f_handShakeFn)(SpixiiSystems *sys, ApplicationSystems *app);

SpixiiSystems g_systems;
ApplicationSystems g_application;

// TODO this should be moved to an event handler class
static void OnEvent(Spixii::Event &event)
{
    if(event.GetEventType() == Spixii::WindowCloseEvent::GetStaticType())
    {
        g_systems.running = false;
        return;
    }
    // Filter or process important events before passing to the application
    if(g_application.application)
    {
        g_application.application->OnEvent(event);
    }

    SPX_TRACE_CORE("OnEvent: {0}", event.ToString());
}

int main(int argc, char **argv)
{
    ::Spixii::Log::Init();

    g_systems = {};
    g_systems.version       = SPIXII_VERSION;
    g_systems.window        = Spixii::Window::Create();
    g_systems.running       = false;

    g_systems.window->SetEventCallback(OnEvent);

#ifdef SPX_PLATFORM_WINDOWS
    HINSTANCE hGetProcIDDLL = LoadLibrary(TEXT("Sandbox.dll"));

    if(!hGetProcIDDLL)
    {
        SPX_ERROR("Could not load the dynamic library");
        return EXIT_FAILURE;
    }

    // resolve function address here
    f_handShakeFn HandShakeFn = (f_handShakeFn)GetProcAddress(hGetProcIDDLL, "HandShake");
    f_handShakeFn ShutdownFn  = (f_handShakeFn)GetProcAddress(hGetProcIDDLL, "Shutdown");
    if(!HandShakeFn || !ShutdownFn)
    {
        SPX_ERROR("could not locate the function");
        return EXIT_FAILURE;
    }

    bool result = HandShakeFn(&g_systems, &g_application);

    if(!result)
    {
        SPX_ERROR_CORE("Could not initialize application");
        return EXIT_FAILURE;
    }
 #endif

    g_systems.running = true;
    g_application.application->OnStatup();

    while(g_systems.running)
    {
        g_systems.window->OnUpdate();
        g_application.application->OnUpdate();
    }

    g_systems.window->Shutdown();
    g_application.application->OnShutdown();

    result = ShutdownFn(&g_systems, &g_application);

    return EXIT_SUCCESS;
}