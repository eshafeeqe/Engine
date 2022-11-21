#pragma once
#include "egpch.h"

#include "Engine/Core.h"
#include "Window.h"

namespace Engine
{
    class ENGINE_API Application
    {
        
    public:
        Application();
        virtual ~Application();

        void run();
        void onEvent(Event& e);

    private:
        bool onWindowClose(Event& e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();
}