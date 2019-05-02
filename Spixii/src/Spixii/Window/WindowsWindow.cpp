#include "spxpch.h"

#ifdef SPX_PLATFORM_WINDOWS

#include "Spixii/Window/WindowsWindow.h"
#include "Spixii/Log.h"

namespace Spixii
{

    Window* Window::Create(const WindowProperties& prop)
    {
        return new WindowsWindow(prop);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& prop)
        : m_properties(prop)
    {
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

        WNDCLASSEX windowClass = { 0 };
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WindowProc;
        windowClass.hInstance = GetModuleHandle(NULL);
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.lpszClassName = windowTitle;
        RegisterClassEx(&windowClass);

        RECT windowRect = { 0, 0, static_cast<LONG>(m_properties.width), static_cast<LONG>(m_properties.height) };
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

    }

    void WindowsWindow::OnUpdate()
    {
        MSG msg = {};
        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
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
        WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        switch (message)
        {
        case WM_CREATE:
        {
            SPX_INFO_CORE("Receivig an CREATE envent");
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        }
        return 0;

        case WM_MOUSEMOVE:
        {
            const int x = LOWORD(lParam);
            const int y = HIWORD(lParam);
            SPX_INFO_CORE("Receivig an KeyDown envent: ({0}, {1})", x, y);
        }
        return 0;

        case WM_KEYDOWN:
            SPX_INFO_CORE("Receivig an KeyDown envent");
            return 0;

        case WM_KEYUP:
            SPX_INFO_CORE("Receivig an KeyUp envent");
            return 0;

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
            SPX_INFO_CORE("Receivig an MouseButtonDown envent");
            return 0;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
            SPX_INFO_CORE("Receivig an MouseButtonUp envent");
            return 0;

        case WM_PAINT:
            return 0;

        case WM_DESTROY:
            SPX_INFO_CORE("Receivig an Destroy envent");
            PostQuitMessage(0);
            return 0;
        }

        // Handle any messages the switch statement didn't.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

#endif