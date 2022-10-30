#include <Engine.h>


class Sandbox : public Engine::Application
{
private:

public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};


Engine::Application* Engine::CreateApplication()
{
    return new Sandbox();
}