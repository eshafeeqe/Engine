
#include "Engine/Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
 
    Application::Application()
    {
        m_Window = Window::Create();
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application()
    {}

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
        EG_CORE_TRACE("{0}", e);
    }

    void Application::run()
    {
        while(m_Running)
        {
            m_Window->OnUpdate();
        }
    }
    
    bool Application::onWindowClose(Event& e)
    {
        m_Running = false;
        return true;
    }

}