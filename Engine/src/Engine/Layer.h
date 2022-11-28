#pragma once 
#include "egpch.h"

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace Engine
{

    class ENGINE_API Layer
    {
    public:
        Layer(const std::string& name ="Layer");

        virtual ~Layer();

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& event) = 0; 
        virtual void OnImGuiRender() = 0; 

        inline const std::string& GetName() const {return m_DebugName;}

    protected:
        std::string m_DebugName;
    };

}