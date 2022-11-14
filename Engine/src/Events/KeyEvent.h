#pragma once

#include "Event.h"
#include "Engine/src/Core.h"

#include "sstream"

namespace Engine
{
    class ENGINE_API KeyEvent : public Event
    {
        public: 
            inline int GetKeyCode() const {return m_KeyCode;}

        
        protected:
            KeyEvent(int keycode)
                :m_keycode(keycode) {}

            int m_KeyCode;

    };

    class ENGINE_API KeyPressedEvent: public KeyEvent
    {
        public:
            KeyPressedEvent(int keycode, int repeatCount)
                : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

            inline int GetRepeatCount() const { return m_RepeatCount;} 

            std::string ToString const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
                return ss; 
            }

        private:
            int m_RepeatCount; 

    }
}