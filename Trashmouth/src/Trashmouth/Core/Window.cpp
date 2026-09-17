#include "Window.h"
#include "GLFW/glfw3.h"
#include "Trashmouth/Core/Event.h"
#include "WindowEvents.h"
#include <Trashmouth/Core/Shader.h>
#include <print>

namespace TM {
    Window::Window(const WindowSpecification &spec) : m_Specification(spec) {}
    Window::~Window() {Destroy();}

    void Window::Create()
    {
        // Initialize GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create GLFW window
        m_Handle = glfwCreateWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title.c_str(), nullptr, nullptr);
        if (m_Handle == NULL)
        {
            std::println("Failed to create GLFW window");
            assert(false);
        }

        glfwMakeContextCurrent(m_Handle);
        glfwSwapInterval(m_Specification.vSync ? 1 : 0);
        glfwSetWindowUserPointer(m_Handle, this);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::println("Failed to initialize GLAD");
            assert(false);
        }

        glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* handle)
        {
            Window& window = *((Window*)glfwGetWindowUserPointer(handle));

            WindowClosedEvent event;
            window.RaiseEvent(event);
        });

        glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* handle, int width, int height)
        {
            Window& window = *((Window*)glfwGetWindowUserPointer(handle));

            WindowResizeEvent event((int)width, (int)height);
            window.RaiseEvent(event);
        });
    }

    void Window::Destroy()
    {
        if (m_Handle) glfwDestroyWindow(m_Handle);
        m_Handle = nullptr;
    }

    void Window::Update()
    {
        glfwSwapBuffers(m_Handle);
    }

    void Window::RaiseEvent(Event& event)
    {
        if (m_Specification.EventCallback) m_Specification.EventCallback(event);
    }

    glm::vec2 Window::GetFramebufferSize() const
    {
        int width, height;
        glfwGetFramebufferSize(m_Handle, &width, &height);
        return { width, height };
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Handle) != 0;
    }
}
