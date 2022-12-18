
#include "Engine/Application.h"
#include "Engine/Renderer/Renderer.h"


namespace Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    
    Application* Application::m_Instance = nullptr;

    Application::Application()
    : m_Camera(-1.0f, 1.0f, -1.0f, 1.0f )
    {
        m_Instance = this;
        EG_CORE_ASSERT(m_Instance, "Application already exists!");
        m_Window = Window::Create();
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));
        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 *7] = {
            -0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.5f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.5f, 1.0f,
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


        BufferLayout layout = { 
            {ShaderDataType::Float3, "a_Position" },
            {ShaderDataType::Float4, "a_Color" },

        };
        
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_SquareVA.reset(VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f, 
             0.75f, -0.75f, 0.0f, 
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f, 

        };

        std::shared_ptr<VertexBuffer> squareVB; 
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        
        squareVB->SetLayout({ 
            {ShaderDataType::Float3, "a_Position" },
            });
        
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareVertices)/sizeof(squareVertices[0])));
        m_SquareVA->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;


            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1);
            }

        )";
        
        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position*0.5 + 0.5, 0.1);
                color = v_Color;
            }

        )";

        m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);

        std::string blueShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            
            
            out vec3 v_Position;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1);
            }

        )";
        
        std::string blueShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_Position;


            void main()
            {
                color = vec4(v_Position*0.5 + 0.5, 0.1);
            }

        )";


        
        m_BlueShader = std::make_unique<Shader>(blueShaderVertexSrc, blueShaderFragmentSrc);

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
            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommand::Clear();
             
            Renderer::BeginScene();

            m_BlueShader->Bind();            
            Renderer::Submit(m_SquareVA);

            m_Shader->Bind();            
            Renderer::Submit(m_VertexArray);

            Renderer::EndScene();

            
            for(auto& layer: m_LayerStack)
            {
                layer->OnUpdate();
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

    void Application::PushLayer(std::shared_ptr<Layer>& layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(std::shared_ptr<Layer>& overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

}