#pragma once

#include "Spixii/Core.h"

namespace Spixii
{
    class Allocator;
    class Event;
    class Window;
    class Application;

    struct SpixiiSystems
    {
        int32              version;
        Spixii::Allocator *globalAllocator;
        Spixii::Window *   window;
        bool *             isRunning;
    };

    struct ApplicationSystems
    {
        int32                version;
        Spixii::Application *application;
        void *               sharedLibrary;
    };

    class Engine
    {
    public:
        static void Initialize();
        static void Shutdown();
        static void Update();

        static void OnEvent(Spixii::Event &event);

        static SpixiiSystems GetSystemView();

    public:
        static Allocator *        s_globalAllocator;
        static Window *           s_window;
        static bool               s_isRunning;
        static ApplicationSystems s_application;
    };

}  // namespace Spixii