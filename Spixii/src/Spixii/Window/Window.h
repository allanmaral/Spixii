#pragma once

#include "spxpch.h"

#include "Spixii/Core.h"
#include "Spixii/Events/Event.h"

namespace Spixii
{
    using EventCallbackFn = std::function<void(Event&)>;

    struct WindowProperties
    {
        std::string title;
        uint32_t width;
        uint32_t height;

        bool VSyncOn;
        EventCallbackFn eventCallback;

        WindowProperties(const std::string& _title  = "Spixii Engine", 
                                   uint32_t _width  = 1280, 
                                   uint32_t _height = 720,
                                   bool     _VSync  = false)
            : title(_title), width(_width), height(_height),
              VSyncOn(_VSync) {}
    };

    class SPIXII_API Window
    {
    public:
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSyncOn() const = 0;

        static Window* Create(const WindowProperties& prop = WindowProperties());
    };

}