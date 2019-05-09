#pragma once

#include "Spixii/Application.h"
#include "Spixii/Base/Engine.h"
#include "Spixii/Core.h"
#include "Spixii/Log.h"
#include "Spixii/Window/Window.h"

#include "Spixii/Events/ApplicationEvent.h"
#include "Spixii/Events/KeyEvent.h"
#include "Spixii/Events/MouseEvent.h"

#ifdef SPX_APPLICATION_IMPLEMENTATION

Spixii::SpixiiSystems Spixii::Application::s_engine;

#ifdef __cplusplus
extern "C"
{
#endif

    __declspec(dllexport) bool __cdecl HandShake(Spixii::SpixiiSystems *engine, Spixii::ApplicationSystems *system)
    {
        Spixii::Application::s_engine = *engine;
        system->version               = SPIXII_VERSION;
        system->application           = Spixii::CreateApplication();
        return engine->version == engine->version;
    }

    __declspec(dllexport) bool __cdecl Shutdown()
    {
        return true;
    }

#ifdef __cplusplus
}
#endif
#endif