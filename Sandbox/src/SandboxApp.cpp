#include <Engine.h>
#include <imgui.h>

class ExampleLayer: public Engine::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f ), m_CameraPosition(0.0f)
    {

        m_VertexArray.reset(Engine::VertexArray::Create());

        float vertices[3 *7] = {
            -0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.5f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.5f, 1.0f,
        };

        std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

        vertexBuffer->SetLayout({ 
            {Engine::ShaderDataType::Float3, "a_Position" },
            {Engine::ShaderDataType::Float4, "a_Color" },

        });
        
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint indices[3] = {0, 1, 2};
        std::shared_ptr<Engine::IndexBuffer> indexBuffer;
        indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);
        m_SquareVA.reset(Engine::VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f, 
             0.75f, -0.75f, 0.0f, 
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f, 

        };

        std::shared_ptr<Engine::VertexBuffer> squareVB; 
        squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        
        squareVB->SetLayout({ 
            {Engine::ShaderDataType::Float3, "a_Position" },
            });
        
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<Engine::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareVertices)/sizeof(squareVertices[0])));
        m_SquareVA->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;
            uniform mat4 u_ViewProjection;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection*vec4(a_Position, 1);
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

        m_Shader = std::make_unique<Engine::Shader>(vertexSrc, fragmentSrc);

        std::string blueShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            
            uniform mat4 u_ViewProjection;
            
            out vec3 v_Position;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection*vec4(a_Position, 1);
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


        
        m_BlueShader = std::make_unique<Engine::Shader>(blueShaderVertexSrc, blueShaderFragmentSrc);


    }
    
    void OnUpdate(Engine::Timestep ts) override
    {

        if(Engine::Input::IsKeyPressed(EG_KEY_LEFT))
            m_CameraPosition.x += m_CameraMoveSpeed*ts;
        else if(Engine::Input::IsKeyPressed(EG_KEY_RIGHT))
            m_CameraPosition.x -= m_CameraMoveSpeed*ts;

        if(Engine::Input::IsKeyPressed(EG_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed*ts;
        else if(Engine::Input::IsKeyPressed(EG_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed*ts;

        if(Engine::Input::IsKeyPressed(EG_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed*ts;
        
        if(Engine::Input::IsKeyPressed(EG_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed*ts;

        Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Engine::RenderCommand::Clear();
            
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
    
        Engine::Renderer::BeginScene(m_Camera);

        Engine::Renderer::Submit(m_BlueShader, m_SquareVA);

        Engine::Renderer::Submit(m_Shader, m_VertexArray);

        Engine::Renderer::EndScene();


    }

    void OnImGuiRender() override
    {
    }

    void OnEvent(Engine::Event& event) override
    {
        
    }

    
private:
        std::shared_ptr <Engine::Shader> m_Shader;
        std::shared_ptr <Engine::Shader> m_BlueShader;

        std::shared_ptr<Engine::VertexArray> m_VertexArray; 
        std::shared_ptr<Engine::VertexArray> m_SquareVA;

        Engine::OrthographicCamera m_Camera;
        
        glm::vec3 m_CameraPosition;
        float m_CameraMoveSpeed = 1.0f;
        
        float m_CameraRotation = 0.0f;
        float m_CameraRotationSpeed = 30.0f;

};

class Sandbox : public Engine::Application
{

public:

    Sandbox()
    {
        std::shared_ptr<Engine::Layer> example_layer = std::make_shared<ExampleLayer>();
        PushLayer(example_layer);
        
    }

    ~Sandbox()
    {

    }
};


Engine::Application* Engine::CreateApplication()
{
    return new Sandbox();

}