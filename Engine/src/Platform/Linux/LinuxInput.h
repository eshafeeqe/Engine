#pragma once 

#include "egpch.h"
#include "Engine/Core.h"
#include "Engine/Input.h"
#include "Engine/Application.h"

#include <GLFW/glfw3.h>

namespace Engine
{
    class LinuxInput : public Input
    {
    
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
        virtual std::pair<float, float> GetMousPositionImpl() override;
    };
    
} // namespace Engine



