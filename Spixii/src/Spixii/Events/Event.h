#pragma once

#include "spxpch.h"

#include "Spixii/Core.h"

namespace Spixii
{
    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowsResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        ApplicationTick,
        ApplicationUpdate,
        ApplicationRender,
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    enum EventCategory
    {
        None                     = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput       = BIT(1),
        EventCategoryKeyboard    = BIT(2),
        EventCategoryMouse       = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::##type; }              \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual uint64_t GetCategoryFlags() const override { return category; }

    class SPIXII_API Event
    {
        friend class EventDispatcher;

    public:
        virtual EventType GetEventType() const    = 0;
        virtual const char *GetName() const       = 0;
        virtual uint64_t GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

    private:
        bool m_handled = false;
    };

    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T &)>;

    public:
        EventDispatcher(Event &event)
            : m_event(event)
        {
        }

        template <typename T>
        bool Dispatch(EventFn<T> func)
        {
            if(m_event.GetEventType() == T::GetStaticType())
            {
                m_event.m_handled = func(*(T *)&m_event);
                return true;
            }
            return false;
        }

    private:
        Event &m_event;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e)
    {
        return os << e.ToString();
    }
}  // namespace Spixii