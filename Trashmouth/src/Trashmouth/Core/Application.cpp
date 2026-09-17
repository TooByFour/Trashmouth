#include "Application.h"
#include "Trashmouth/Core/Event.h"
#include "Window.h"
#include <memory>
#include <ranges>
#include <assert.h>
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include "GLFW/glfw3.h"

namespace TM
{
    static Application *s_Application = nullptr;

    Application::Application(const ApplicationSpecification &spec) : m_Specification(spec)
    {
        s_Application = this;

        glfwInit();

        m_Specification.WindowSpecification.EventCallback = [this](Event& event) {RaiseEvent(event);};
        m_Window = std::make_shared<Window>(m_Specification.WindowSpecification);
        m_Window->Create();
    }

    Application::~Application()
    {
        m_Window->Destroy();
        glfwTerminate();
        s_Application = nullptr;
    }

    void Application::Run()
    {
        m_Running = true;

        float lastTime = GetTime();

        while (m_Running)
        {
            glfwPollEvents();

            if(m_Window->ShouldClose())
            {
                Stop();
                break;
            }

            float currentTime = GetTime();
            float timeStep = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
            lastTime = currentTime;

            for (const std::unique_ptr<Layer> &layer : m_LayerStack) layer->OnUpdate(timeStep);
            for (const std::unique_ptr<Layer> &layer : m_LayerStack) layer->OnRender();

            m_Window->Update();
        }
    }

    void Application::Stop()
    {
        m_Running = false;
    }

    void Application::RaiseEvent(Event &event)
    {
        for (auto &layer : std::views::reverse(m_LayerStack))
        {
            layer->OnEvent(event);
            if (event.Handled) break;
        }
    }

    glm::vec2 Application::GetFramebufferSize() const
    {
        return m_Window->GetFramebufferSize();
    }

    Application &Application::Get()
    {
        assert(s_Application);
        return *s_Application;
    }

    float Application::GetTime()
    {
        return glfwGetTime();
    }

}
