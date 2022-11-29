#pragma once
#include "egpch.h"

#include "imgui.h"

#include "Engine/Layer.h"
#include "Engine/Core.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"


#include "Engine/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Engine {

    class ImGuiLayer : public Layer
    {

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        virtual void Begin() override;
        virtual void End() override;


    private:
        float m_Time = 0.0f;
    };
    
    
}