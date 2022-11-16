
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Engine
{
 
    Application::Application()
    {}

    Application::~Application()
    {}

    void Application::run()
    {
        WindowResizeEvent e(1280, 700);
        EG_TRACE(e);

        while (true);
    }


}