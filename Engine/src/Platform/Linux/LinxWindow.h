#pragma once
#include "egpch.h"

#include "Engine/Window.h"


#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/KeyEvent.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


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
    
        inline virtual void* GetNativeWindow() const override {return m_Window;};   

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
    };


}