#pragma once
#include <iostream>

extern Engine::Application* CreateApplication();

int main (int argc, char** argv)
{
    std::cout<<"from entry point";
    auto app = Engine::CreateApplication(); 
    app->run();
    delete app;

}




