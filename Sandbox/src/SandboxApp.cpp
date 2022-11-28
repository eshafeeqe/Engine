#include <Engine.h>

class ExampleLayer: public Engine::Layer
{
    public:
        ExampleLayer()
            : Layer("Example") {}
        
        void OnUpdate() override
        {
            if(Engine::Input::IsKeyPressed(EG_KEY_TAB))
                EG_TRACE("Tab Key Pressed!");
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
        
        std::shared_ptr<Engine::Layer> imgui_layer = std::make_shared<Engine::ImGuiLayer>();
        PushOverlay(imgui_layer);
        //auto imgui_layer = 
    }

    ~Sandbox()
    {

    }
};


Engine::Application* Engine::CreateApplication()
{
    return new Sandbox();

}