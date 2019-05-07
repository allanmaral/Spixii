#pragma once

#include "spxpch.h"

#include "Spixii/Core.h"
#include "Spixii/Events/Event.h"

namespace Spixii
{
    typedef void(*EventCallbackFn)(Event &);

    struct WindowProperties
    {
        std::string title;
        uint32 width;
        uint32 height;

        bool VSyncOn;
        EventCallbackFn eventCallback;

        WindowProperties(const std::string &_title = "Spixii Engine",
                         uint32 _width           = 1280,
                         uint32 _height          = 720,
                         bool _VSync               = false)
            : title(_title)
            , width(_width)
            , height(_height)
            , VSyncOn(_VSync)
        {
        }
    };

    class SPIXII_API Window
    {
    public:
        virtual ~Window() = default;

        virtual void Shutdown() = 0;

        virtual void OnUpdate() = 0;

        virtual uint32 GetWidth() const = 0;
        virtual uint32 GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSyncOn() const = 0;

        static Window *Create(const WindowProperties &prop = WindowProperties());
    };

}  // namespace Spixii