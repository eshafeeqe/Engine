#pragma once
#include <iostream>

extern Engine::Application* CreateApplication();

int main (int argc, char** argv)
{
    Engine::Log::Init();
    Engine::Log::GetCoreLogger()->warn("Initialized Log!");
    Engine::Log::GetClientLogger()->info("Hello!");

    auto app = Engine::CreateApplication(); 
    app->run();
    delete app;

}




