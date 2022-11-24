#include <Engine.h>

class ExampleLayer: public Engine::Layer
{
    public:
        ExampleLayer()
            : Layer("Example") {}
        
        void OnUpdate() override
        {
            EG_INFO("ExampleLayer: Update");
        }

        void OnEvent(Engine::Event& event) override
        {
            EG_TRACE("{0}", event);
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


std::unique_ptr<Engine::Application> Engine::CreateApplication()
{
    return std::make_unique<Sandbox>();

}