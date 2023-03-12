
#include "Engine/Application.h"
#include "Engine/Renderer/Renderer.h"


namespace Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    
    Application* Application::m_Instance = nullptr;

    Application::Application()
    {
        m_Instance = this;
        EG_CORE_ASSERT(m_Instance, "Application already exists!");
        m_Window = Window::Create();
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));

        Renderer::Init();
        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer);

        
    }

    Application::~Application()
    {}

    Application* Application::Get()
    {
        return m_Instance;
    }

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
        
        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.Handled)
                break;
        }
    }

    void Application::run()
    {
        while(m_Running)
        {
            float time = (float)glfwGetTime(); 
            Timestep timestep = time - m_LastFrameTime;
             
            m_LastFrameTime = time;
            for(auto& layer: m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            
            for(auto& layer: m_LayerStack)
            {
                layer->OnImGuiRender();
            }

            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }
    
    bool Application::onWindowClose(Event& e)
    {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Ref<Layer>& layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Ref<Layer>& overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

}