#include "LinuxInput.h"

namespace  Engine
{
    Input* Input::s_Instance =  new LinuxInput();

    bool LinuxInput::IsKeyPressedImpl(int keycode)
    {

        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;

    }

    bool LinuxInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::GetMousPositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetNativeWindow());
        double  xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos); 

        return {float(xpos), float(ypos)};
     
    }

    float LinuxInput::GetMouseXImpl()
    {
        auto [xpos, ypos] = GetMousPositionImpl();

        return xpos;
        
    }

    float LinuxInput::GetMouseYImpl()
    {
        auto [xpos, ypos] = GetMousPositionImpl();
        return ypos;       
    }

}