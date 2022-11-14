#pragma once

#include "Core.h"

namespace Engine
{
    class ENGINE_API Application
    {
    private:
        
    public:
        Application();
        virtual ~Application();

        void run();
    };

    Application* CreateApplication();
}