#pragma once

#include "Event.h"
#include <format>

namespace TM
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}

        static EventType GetStaticType() { return EventType::WindowResize;}
        EventType GetEventType() const override { return EventType::WindowResize; }
        const char *GetName() const override { return "WindowResize"; }
        std::string ToString() const override { return std::format("WindowResize: {}, {}", m_Width, m_Height); }

    private:
        int m_Width, m_Height;
    };

    class WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() {}
        static EventType GetStaticType() { return EventType::WindowClose;}
        EventType GetEventType() const override { return EventType::WindowClose; }
        const char *GetName() const override { return "WindowClosed"; }
        std::string ToString() const override { return "WindowClosed"; }
    };
}
