#pragma once
#include "egpch.h"

#include "Engine/Layer.h"

namespace Engine {

    class ImGuiLayer : public Layer
    {

    public:
        ImGuiLayer();
        ~ImGuiLayer();

    private:

        void OnUpdate();
        void OnEvent(Event& event);
        void OnAttach();
        void OnDetach(); 
    };
    
    
}