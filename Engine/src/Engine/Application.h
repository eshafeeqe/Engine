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

        void PushLayer(std::shared_ptr<Layer>& layer);
        void PushOverlay(std::shared_ptr<Layer>& overlay);

        inline std::unique_ptr<Window>& GetWindow(){ return m_Window; }

        static Application* Get();

        bool onWindowClose(Event& e);
    
    protected:
        Application();
        Application(const Application& rs);
        Application& operator =(const Application& rs);

        
    private:

        std::unique_ptr<Window> m_Window;
        std::shared_ptr<Layer> m_ImGuiLayer;
        std::unique_ptr <Shader> m_Shader;
        
        std::unique_ptr <Shader> m_BlueShader;

        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        
        std::shared_ptr<VertexArray> m_SquareVA;

        OrthographicCamera m_Camera;
            
        bool m_Running = true;
        LayerStack m_LayerStack;
    
        static Application* m_Instance;
    

    };

    Application* CreateApplication();
}