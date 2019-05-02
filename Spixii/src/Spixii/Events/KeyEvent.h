#pragma once

#include "Spixii/Events/Event.h"
#include "Spixii/Input/InputKeys.h"

namespace Spixii
{

    class SPIXII_API KeyEvent : public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        inline SPX_KEYBOARD_KEY GetKeyCode() const { return m_keyCode; }

    protected:
        KeyEvent(SPX_KEYBOARD_KEY keyCode)
            : m_keyCode(keyCode)
        {
        }

        SPX_KEYBOARD_KEY m_keyCode;
    };

    class SPIXII_API KeyPressedEvent : public KeyEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyPressed)

    public:
        KeyPressedEvent(SPX_KEYBOARD_KEY keyCode, uint32_t repeatCount)
            : KeyEvent(keyCode)
            , m_repeatCount(repeatCount)
        {
        }

        inline uint32_t GetRepeatCount() const { return m_repeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

    private:
        uint32_t m_repeatCount;
    };

    class SPIXII_API KeyReleasedEvent : public KeyEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyReleased)

    public:
        KeyReleasedEvent(SPX_KEYBOARD_KEY keyCode)
            : KeyEvent(keyCode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }
    };
}  // namespace Spixii