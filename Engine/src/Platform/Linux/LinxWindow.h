#pragma once
#include "egpch.h"

#include "Engine/Window.h"

#include <GLFW/glfw3.h>


namespace Engine
{
    class LinuxWindow : public Window
    {
    public:
        LinuxWindow(const WindowProps& props);
        virtual ~LinuxWindow();

        void OnUpdate() override;

        inline uint GetWidth() const override { return m_Data.Width;}
        inline uint GetHeight() const override { return m_Data.Height;}

        // Window attributes

        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback;}
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;
    
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:

        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            uint Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };
        
        WindowData m_Data;
    }


}