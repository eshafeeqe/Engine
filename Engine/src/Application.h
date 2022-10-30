#pragma once

namespace Engine
{
    class Application
    {
    private:
        
    public:
        Application();
        virtual ~Application();

        void run();
    };

    Application* CreateApplication();
}