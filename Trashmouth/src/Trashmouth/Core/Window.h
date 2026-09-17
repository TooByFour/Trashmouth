#pragma once

#include "Event.h"

// GLFW must not include a platform OpenGL header; GLAD is the OpenGL loader.
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <functional>

/**
 * Following this tutorial: https://www.youtube.com/watch?v=rUxZ5N77M5E&list=PLlrATfBNZ98cpX2LuxLnLyLEmfD2FPpRA
 */
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
