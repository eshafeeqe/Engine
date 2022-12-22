#pragma once
#include "egpch.h"

#include "Engine/Core.h"
#include "Engine/Window.h"
#include "Engine/Input.h"
#include "Engine/Log.h"
#include "Engine/LayerStack.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Core/Timestep.h"

#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"


namespace Engine
{
    class ENGINE_API Application  
    {
        
    public:
        virtual ~Application();

        void run();
        void onEvent(Event& e);

        void PushLayer(Ref<Layer>& layer);
        void PushOverlay(Ref<Layer>& overlay);

        inline Ref<Window>& GetWindow(){ return m_Window; }

        static Application* Get();

        bool onWindowClose(Event& e);
    
    protected:
        Application();
        Application(const Application& rs);
        Application& operator =(const Application& rs);

        
    private:

        Ref<Window> m_Window;
        Ref<Layer> m_ImGuiLayer;
                   
        bool m_Running = true;
        LayerStack m_LayerStack;
        Timestep m_LastFrameTime;

    private:

        static Application* m_Instance;
    

    };

    Application* CreateApplication();
}