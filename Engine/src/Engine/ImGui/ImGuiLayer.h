#pragma once
#include "egpch.h"
#include "imgui.h"

#include "Engine/Layer.h"
#include "GLFW/glfw3.h"
#include "Engine/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

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
        float m_Time = 0.0f;
    };
    
    
}