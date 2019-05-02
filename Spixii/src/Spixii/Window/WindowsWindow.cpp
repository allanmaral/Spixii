#include "spxpch.h"

#ifdef SPX_PLATFORM_WINDOWS

#include "Spixii/Log.h"
#include "Spixii/Window/WindowsWindow.h"

// Include Events
#include "Spixii/Events/ApplicationEvent.h"
#include "Spixii/Events/KeyEvent.h"
#include "Spixii/Events/MouseEvent.h"

// Include Input Key codes
#include "Spixii/Input/InputKeys.h"

namespace Spixii
{

    Window *Window::Create(const WindowProperties &prop)
    {
        return new WindowsWindow(prop);
    }

    WindowsWindow::WindowsWindow(const WindowProperties &prop)
        : m_properties(prop)
    {
        memset(m_KeyRepeat, 0, SPX_MAX_KEY_CODE);
        Init();
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init()
    {
        SPX_INFO_CORE("Creating a Windows window: {0} ({1} x {2})", m_properties.title, m_properties.width, m_properties.height);

        wchar_t windowTitle[256];
        size_t titleSize = 0;
        mbstowcs_s(&titleSize, windowTitle, (size_t)256, m_properties.title.c_str(), 256);

        WNDCLASSEX windowClass    = {0};
        windowClass.cbSize        = sizeof(WNDCLASSEX);
        windowClass.style         = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc   = WindowProc;
        windowClass.hInstance     = GetModuleHandle(NULL);
        windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
        windowClass.lpszClassName = windowTitle;
        RegisterClassEx(&windowClass);

        RECT windowRect = {0, 0, static_cast<LONG>(m_properties.width), static_cast<LONG>(m_properties.height)};
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

        m_windowHandle = CreateWindow(
            windowClass.lpszClassName,
            windowTitle,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top,
            nullptr,
            nullptr,
            windowClass.hInstance,
            this);

        ShowWindow(m_windowHandle, SW_SHOW);
    }

    void WindowsWindow::Shutdown()
    {
        PostQuitMessage(0);
        DestroyWindow(m_windowHandle);
        m_windowHandle = nullptr;
    }

    void WindowsWindow::OnUpdate()
    {
        MSG msg = {};
        while(PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                // Handle QUIT differently??
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        m_properties.VSyncOn = enabled;
    }

    bool WindowsWindow::IsVSyncOn() const
    {
        return m_properties.VSyncOn;
    }

    // Main message handler
    LRESULT CALLBACK WindowsWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        WindowsWindow *window = reinterpret_cast<WindowsWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        switch(message)
        {
        case WM_CREATE:
        {
            SPX_INFO_CORE("Receivig an CREATE envent");
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
            return 0;
        }

        case WM_SIZING:
        {
            RECT dummyRect = {0, 0, 0, 0};
            LONG xOffset, yOffset;
            AdjustWindowRect(&dummyRect, WS_OVERLAPPEDWINDOW, FALSE);
            xOffset = dummyRect.right - dummyRect.left;
            yOffset = dummyRect.bottom - dummyRect.top;

            RECT *rect                  = reinterpret_cast<RECT *>(lParam);
            window->m_properties.width  = rect->right - rect->left - xOffset;
            window->m_properties.height = rect->bottom - rect->top - yOffset;

            WindowResizeEvent event(window->m_properties.width, window->m_properties.height);
            window->m_properties.eventCallback(event);
            return 0;
        }

        case WM_KEYDOWN:
        {
            const uint32_t repeatCount    = lParam & 0xffff;
            const int32_t scanCode        = (lParam >> 16) & 0x1ff;
            const uint32_t firstTime      = (lParam >> 30) & 1;
            window->m_KeyRepeat[scanCode] = window->m_KeyRepeat[scanCode] * firstTime + repeatCount;
            KeyPressedEvent event((SPX_KEYBOARD_KEY)scanCode, window->m_KeyRepeat[scanCode]);
            window->m_properties.eventCallback(event);
            return 0;
        }

        case WM_KEYUP:
        {
            const int scanCode = (lParam >> 16) & 0x1ff;
            KeyReleasedEvent event((SPX_KEYBOARD_KEY)scanCode);
            window->m_properties.eventCallback(event);
            return 0;
        }

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
        {
            SPX_MOUSE_BUTTON button = SPX_MOUSE_BUTTON_UNKNOWN;
            if(message == WM_LBUTTONDOWN)
            {
                button = SPX_MOUSE_BUTTON_LEFT;
            }
            else if(message == WM_RBUTTONDOWN)
            {
                button = SPX_MOUSE_BUTTON_RIGHT;
            }
            else if(message == WM_MBUTTONDOWN)
            {
                button = SPX_MOUSE_BUTTON_MIDDLE;
            }
            // TODO: Map all other possible mouse keys
            MouseButtonPressedEvent event(button);
            window->m_properties.eventCallback(event);
            return 0;
        }

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
        {
            SPX_MOUSE_BUTTON button = SPX_MOUSE_BUTTON_UNKNOWN;
            if(message == WM_LBUTTONUP)
            {
                button = SPX_MOUSE_BUTTON_LEFT;
            }
            else if(message == WM_RBUTTONUP)
            {
                button = SPX_MOUSE_BUTTON_RIGHT;
            }
            else if(message == WM_MBUTTONUP)
            {
                button = SPX_MOUSE_BUTTON_MIDDLE;
            }
            // TODO: Map all other possible mouse keys
            MouseButtonReleasedEvent event(button);
            window->m_properties.eventCallback(event);
            return 0;
        }

        case WM_MOUSEWHEEL:
        {
            MouseScrolledEvent event(0.0f, (SHORT)HIWORD(wParam) / (float)WHEEL_DELTA);
            window->m_properties.eventCallback(event);
            return 0;
        }

        case WM_MOUSEHWHEEL:
        {
            // NOTE: The X-axis is inverted for consistency with macOS and X11
            MouseScrolledEvent event(-((SHORT)HIWORD(wParam) / (float)WHEEL_DELTA), 0.0f);
            window->m_properties.eventCallback(event);
            return 0;
        }

        case WM_MOUSEMOVE:
        {
            const int x = LOWORD(lParam);
            const int y = HIWORD(lParam);
            MouseMovedEvent event((float)x, (float)y);
            window->m_properties.eventCallback(event);
            return 0;
        }

            /*case WM_PAINT:
            return 0;*/

        case WM_CLOSE:
        {
            WindowCloseEvent event;
            window->m_properties.eventCallback(event);
            return 0;
        }

            /*case WM_DESTROY:
        {
            WindowCloseEvent event;
            window->m_properties.eventCallback(event);
            PostQuitMessage(0);
            return 0;
        }*/
        }

        // Handle any messages the switch statement didn't.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }  // namespace Spixii
}  // namespace Spixii

#endif