#pragma once

#include "Spixii/Window/Window.h"

#ifdef SPX_PLATFORM_WINDOWS

namespace Spixii
{

#define SPX_MAX_KEY_CODE 0x1ff

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties &prop);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline uint32_t GetWidth() const { return m_properties.width; };
        inline uint32_t GetHeight() const { return m_properties.height; }

        void SetEventCallback(const EventCallbackFn &callback) override { m_properties.eventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSyncOn() const override;

    private:
        void Init();
        void Shutdown();

        // Needed to preocess window events
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        HWND m_windowHandle;
        WindowProperties m_properties;
        LONG m_KeyRepeat[SPX_MAX_KEY_CODE];
    };
}  // namespace Spixii

#endif