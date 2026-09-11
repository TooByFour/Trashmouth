#pragma once

#include <Trashmouth/tmpch.h>

namespace TM {
enum EventType {
  None = 0,
  WindowClose,
  WindowResize,
  KeyPressed,
  KeyReleased,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

class Event {
public:
  bool Handled = false;

  virtual ~Event() {}
  virtual EventType GetEventType() const = 0;
  virtual const char *GetName() const = 0;
  virtual std::string ToString() const { return GetName(); }
};

class EventDispatcher {
public:
  EventDispatcher(Event &event) : m_Event(event) {}

  template <typename T> bool Dispatch(std::function<bool(T &)> func) {
    if (m_Event.GetEventType() == T::GetStaticType() && !m_Event.Handled) {
      m_Event.Handled = func(*(T *)&m_Event);
      return true;
    }
    return false;
  }

private:
  Event &m_Event;
};
} // namespace TM
