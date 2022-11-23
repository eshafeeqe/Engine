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
        virtual ~Application();

        void run();
        void onEvent(Event& e);

        void PushLayer(std::shared_ptr<Layer>& layer);
        void PushOverlay(std::shared_ptr<Layer>& overlay);

        inline std::unique_ptr<Window>& GetWindow(){ return m_Window; }

        static std::shared_ptr<Application>& Get();

        bool onWindowClose(Event& e);
    
    protected:
        Application();
        Application(const Application& rs);
        Application& operator =(const Application& rs);

        
    private:

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    
        static std::shared_ptr<Application> m_Instance;
        static std::mutex m_Mutex;

    };

    std::unique_ptr<Engine::Application> CreateApplication();
}