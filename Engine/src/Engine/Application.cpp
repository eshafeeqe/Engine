
#include "Engine/Application.h"


namespace Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    
    Application* Application::m_Instance = nullptr;
    std::mutex Application::m_Mutex;

    Application::Application()
    {
        m_Instance = this;
        EG_CORE_ASSERT(m_Instance, "Application already exists!");
        m_Window = Window::Create();
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application()
    {}

    Application* Application::Get()
    {
        return m_Instance;
    }

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
        //EG_CORE_TRACE("{0}", e);

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.Handled)
                break;
        }
    }

    void Application::run()
    {
        while(m_Running)
        {
            glClearColor(1, 0, 1 ,1);
            glClear(GL_COLOR_BUFFER_BIT);

            for(auto& layer: m_LayerStack)
            {
                layer->OnUpdate();
            }
            
            m_Window->OnUpdate();
        }
    }
    
    bool Application::onWindowClose(Event& e)
    {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(std::shared_ptr<Layer>& layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(std::shared_ptr<Layer>& overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

}