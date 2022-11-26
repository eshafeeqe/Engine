#pragma once
#include "egpch.h"
#include "imgui.h"

#include "Engine/Layer.h"
#include "Engine/Core.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {

    class ImGuiLayer : public Layer
    {

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnUpdate();
        void OnEvent(Event& event);
        void OnAttach();
        void OnDetach(); 
    
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);

    private:
        float m_Time = 0.0f;
    };
    
    
}