#pragma once

#include "Spixii/Events/Event.h"

namespace Spixii
{
    struct SpixiiSystems;

    class Application
    {
    public:
        virtual void Initialize() = 0;

        virtual void OnUpdate() = 0;
        virtual void OnShutdown() = 0;

        virtual void OnEvent(Event &event) = 0;

    public:
        static SpixiiSystems s_engine;
    };

    // Needs to be defined in the client
    Application *CreateApplication();
}  // namespace Spixii
