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
        auto example_layer = std::dynamic_pointer_cast<ExampleLayer::Layer>(std::make_shared<ExampleLayer>());
        PushLayer(example_layer);
    }

    ~Sandbox()
    {

    }
};


std::unique_ptr<Engine::Application> Engine::CreateApplication()
{
    return std::make_unique<Sandbox>();

}