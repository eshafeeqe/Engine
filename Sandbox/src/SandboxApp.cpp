#include "Platform/OpenGL/OpenGLShader.h"
#include <Engine.h>
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer: public Engine::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f ), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
    {

        m_VertexArray.reset(Engine::VertexArray::Create());

        float vertices[3 *7] = {
            -0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.5f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.5f, 1.0f,
        };

        Engine::Ref<Engine::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

        vertexBuffer->SetLayout({ 
            {Engine::ShaderDataType::Float3, "a_Position" },
            {Engine::ShaderDataType::Float4, "a_Color" },

        });
        
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint indices[3] = {0, 1, 2};
        Engine::Ref<Engine::IndexBuffer> indexBuffer;
        indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);
        m_SquareVA.reset(Engine::VertexArray::Create());

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,};

        Engine::Ref<Engine::VertexBuffer> squareVB; 
        squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        
        
        squareVB->SetLayout({  
            {Engine::ShaderDataType::Float3, "a_Position" },
            {Engine::ShaderDataType::Float2, "a_TexCoord" },
            });
        
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Engine::Ref<Engine::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices)/sizeof(squareIndices[0])));
        m_SquareVA->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection*u_Transform*vec4(a_Position, 1);
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

        m_Shader.reset(Engine::Shader::Create(vertexSrc, fragmentSrc));

        std::string flatColorShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            
            
            out vec3 v_Position;
            out vec4 v_Color;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection*u_Transform*vec4(a_Position, 1);
            }

        )";
        
        std::string flatColorShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            uniform vec3 u_Color;

            void main()
            {
                color = vec4(u_Color, 1.0);
            }

        )"; 

        m_FlatColorShader.reset(Engine::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

        std::string textureShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            
            out vec2 v_TexCoord;
            
            void main()
            {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection*u_Transform*vec4(a_Position, 1);
            }

        )";
        
        std::string textureShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            
            in vec2 v_TexCoord;

            uniform sampler2D u_Texture;

            void main()
            {
                color = texture(u_Texture, v_TexCoord);
            }

        )"; 

        m_TextureShader.reset(Engine::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
        m_Texture = Engine::Texture2D::Create("/home/elan/Dev/Engine/Sandbox/assets/textures/Checkerboard.png");

        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->UploadUniformInt(0, "u_Texture");

    }
    
    void OnUpdate(Engine::Timestep ts) override
    {

        if(Engine::Input::IsKeyPressed(EG_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed*ts;
        else if(Engine::Input::IsKeyPressed(EG_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed*ts;

        if(Engine::Input::IsKeyPressed(EG_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed*ts;
        else if(Engine::Input::IsKeyPressed(EG_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed*ts;

        if(Engine::Input::IsKeyPressed(EG_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed*ts;
        
        if(Engine::Input::IsKeyPressed(EG_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed*ts;

        if(Engine::Input::IsKeyPressed(EG_KEY_J))
            m_SquarePosition.x -= m_SquareMoveSpeed*ts;
        else if(Engine::Input::IsKeyPressed(EG_KEY_L))
            m_SquarePosition.x += m_SquareMoveSpeed*ts;

        if(Engine::Input::IsKeyPressed(EG_KEY_I))
            m_SquarePosition.y -= m_SquareMoveSpeed*ts;
        else if(Engine::Input::IsKeyPressed(EG_KEY_K))
            m_SquarePosition.y += m_SquareMoveSpeed*ts;

        Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Engine::RenderCommand::Clear();
            
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation); 
    
        Engine::Renderer::BeginScene(m_Camera);
        
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1));

        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3(m_SquareColor, "u_Color");

        for(int y = 0; y < 20; y++)
        {
            for(int x = 0; x < 20; x++)
            {
                
                glm::vec3 pos(x* 0.11f, y*0.11f, 0.0f );
                glm::mat4 transform = glm::translate(glm::mat4(1.0), pos)*scale;    

                Engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }
        
       
        m_Texture->Bind();
        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_TextureShader)->Bind();
        Engine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        //Engine::Renderer::Submit(m_Shader, m_VertexArray);

        Engine::Renderer::EndScene();


    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Engine::Event& event) override
    {
        
    }

    
private:
        Engine::Ref <Engine::Shader> m_Shader;
        Engine::Ref <Engine::Shader> m_FlatColorShader;
        Engine::Ref <Engine::Shader> m_TextureShader;

        Engine::Ref<Engine::VertexArray> m_VertexArray; 
        Engine::Ref<Engine::VertexArray> m_SquareVA;

        Engine::Ref<Engine::Texture2D> m_Texture;

        Engine::OrthographicCamera m_Camera;
        
        glm::vec3 m_CameraPosition;
        float m_CameraMoveSpeed = 5.0f;
        
        float m_CameraRotation = 0.0f;
        float m_CameraRotationSpeed = 30.0f;

        glm::vec3 m_SquarePosition;
        float m_SquareMoveSpeed = 1.0f;

        glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};   

};

class Sandbox : public Engine::Application
{

public:

    Sandbox()
    {
        Engine::Ref<Engine::Layer> example_layer = std::make_shared<ExampleLayer>();
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