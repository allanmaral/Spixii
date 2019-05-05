#pragma once

#include "Spixii/Application.h"
#include "Spixii/Core.h"
#include "Spixii/Log.h"
#include "Spixii/Window/Window.h"

#include "Spixii/Events/ApplicationEvent.h"
#include "Spixii/Events/KeyEvent.h"
#include "Spixii/Events/MouseEvent.h"

struct SpixiiSystems
{
    int32_t version;
    Spixii::Window *window;
    bool running;
};

struct ApplicationSystems
{
    int32_t version;
    Spixii::Application *application;
};

#ifdef SPX_APPLICATION_IMPLEMENTATION

SpixiiSystems Spixii::Application::s_engine;

#ifdef __cplusplus
extern "C"
{
#endif

    __declspec(dllexport) bool __cdecl HandShake(SpixiiSystems *engine, ApplicationSystems *system)
    {
        Spixii::Application::s_engine = *engine;
        system->version               = SPIXII_VERSION;
        system->application           = Spixii::CreateApplication();
        return engine->version == engine->version;
    }

    __declspec(dllexport) bool __cdecl Shutdown(SpixiiSystems *engine, ApplicationSystems *system)
    {
        delete system->application;
        return true;
    }

#ifdef __cplusplus
}
#endif

#endif