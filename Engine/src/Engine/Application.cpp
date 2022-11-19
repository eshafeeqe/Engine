
#include "Engine/Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Engine
{
 
    Application::Application()
    {
        m_Window = Window::Create();
    }

    Application::~Application()
    {}

    void Application::run()
    {
        while(m_Running)
        {
            m_Window->OnUpdate();
        }
    }


}