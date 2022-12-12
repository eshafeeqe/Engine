
#include "Engine/Application.h"


namespace Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Bool:   return GL_BOOL;

        }

        EG_ASSERT(false, " Unkown ShaderDataType!")
    }

    Application* Application::m_Instance = nullptr;
    std::mutex Application::m_Mutex;

    Application::Application()
    {
        m_Instance = this;
        EG_CORE_ASSERT(m_Instance, "Application already exists!");
        m_Window = Window::Create();
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));
        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);
        
        float vertices[3 *3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


        BufferLayout layout = { 
            {ShaderDataType::Float3, "a_Position" },
            {ShaderDataType::Float3, "a_Color" },
        };

        uint32_t index = 0;
        for (const auto& element: layout)
        {
            glEnableVertexAttribArray(index); 
            glVertexAttribPointer (index, 
                                   element.GetComponentCount(), 
                                   ShaderDataTypeToOpenGLBaseType(element.Type), 
                                   element.Normalized ? GL_TRUE : GL_FALSE, 
                                   layout.GetStride(), 
                                   (const void*)element.Offset); 
            index++;

        }
        
        uint indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));


        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1);
            }

        )";
        
        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_Position;

            void main()
            {
                color = vec4(v_Position*0.5 + 0.5, 0.1);
            }

        )";

        m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);

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
            glClearColor(0.1f, 0.1f, 0.1f ,1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            m_Shader->Bind();
            
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr); 
            glBindVertexArray(0);

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