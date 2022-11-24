
#include "Engine/Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    
    std::shared_ptr<Application> Application::m_Instance = nullptr;
    std::mutex Application::m_Mutex;

    Application::Application()
    {
        EG_CORE_ASSERT(!m_Instance, "Application already exists!");
        m_Window = Window::Create();
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application()
    {}

    std::shared_ptr<Application>& Application::Get()
    {

        if(!m_Instance)
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_Instance = std::shared_ptr<Application>(new Application());
        }
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
            m_Window->OnUpdate();

            for(auto& layer: m_LayerStack)
            {
                layer->OnUpdate();
            }
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