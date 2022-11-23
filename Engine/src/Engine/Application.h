#pragma once
#include "egpch.h"

#include "Engine/LayerStack.h"
#include "Engine/Core.h"
#include "Engine/Window.h"
#include "Engine/Events/ApplicationEvent.h"

namespace Engine
{
    class ENGINE_API Application 
    {
        
    public:
        Application();
        virtual ~Application();

        void run();
        void onEvent(Event& e);

        void PushLayer(std::shared_ptr<Layer>& layer);
        void PushOverlay(std::shared_ptr<Layer>& overlay);

        inline std::unique_ptr<Window>& GetWindow(){ return m_Window; }
        inline std::unique_ptr<Window>& GetWindow(){ return m_Window; }

        static std::weak_ptr<Application>& Get();

    private:
        bool onWindowClose(Event& e);
        
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    
    private:
        static std::weak_ptr<Application> s_Instance;

    };

    Application* CreateApplication();
}