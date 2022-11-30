#include <Engine.h>
#include <imgui.h>

class ExampleLayer: public Engine::Layer
{
    public:
        ExampleLayer()
            : Layer("Example") 
        {

        }
        
        void OnUpdate() override
        {
            if(Engine::Input::IsKeyPressed(EG_KEY_TAB))
                EG_TRACE("Tab Key Pressed!");
        }

        void OnImGuiRender() override
        {
            ImGui::Begin("Test");
            ImGui::Text("Hello World");
            ImGui::End();

        }

        void OnEvent(Engine::Event& event) override
        {
        
        }

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