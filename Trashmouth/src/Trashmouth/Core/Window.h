#pragma once

#include "Event.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <functional>

namespace TM
{
    struct WindowSpecification
    {
        std::string Title;
        int Width = 1280, Height = 720;
        bool IsResizeable = true, vSync = true;

        using EventCallbackFn = std::function<void(Event&)>;
        EventCallbackFn EventCallback;
    };

    class Window
    {
        public:
            Window(const WindowSpecification &spec = WindowSpecification());
            ~Window();

            void Create();
            void Destroy();

            void Update();

            void RaiseEvent(Event& event);

            glm::vec2 GetFramebufferSize() const;
            glm::vec2 GetMousePos() const;
            bool ShouldClose() const;

            GLFWwindow*GetHandle() const { return m_Handle; }
        private:
            WindowSpecification m_Specification;

            GLFWwindow* m_Handle = nullptr;
    };
}
