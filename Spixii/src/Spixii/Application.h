#pragma once

#include "Spixii/Core.h"
#include "Spixii/Window/Window.h"

#include "Spixii/Events/ApplicationEvent.h"
#include "Spixii/Log.h"
#include "Spixii/Window/Window.h"

namespace Spixii
{
    template class SPIXII_API std::_Compressed_pair<std::default_delete<Spixii::Window>, Spixii::Window *, true>;
    template class SPIXII_API std::unique_ptr<Spixii::Window, std::default_delete<Spixii::Window>>;

    class SPIXII_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event &event);

    private:
        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        bool OnWindowClose(WindowCloseEvent &event);

    private:
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    // Needs to be defined in the client
    Application *CreateApplication();
}  // namespace Spixii
