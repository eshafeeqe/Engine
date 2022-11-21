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

        virtual void OnAttach(){}
        virtual void OnDetach(){}
        virtual void OnUpdate(){}
        virtual void OnEvent(Event& event){}

        inline const std::string& GetName() const {return m_DeubName;}

    protected:
        std::string m_DebugName;
    };

}