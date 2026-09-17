#include "AppLayer.h"
#include "Trashmouth/Core/Application.h"
#include "Trashmouth/Core/Event.h"
#include "Trashmouth/Core/Shader.h"
#include "Trashmouth/Core/WindowEvents.h"
#include <print>

AppLayer::AppLayer()
{
    std::println("Created AppLayer");

    m_Shader = TM::Shader::CreateShader("Shaders/shader.vert.glsl", "Shaders/shader.frag.glsl");

    glCreateVertexArrays(1, &m_VertexArray);
    glCreateBuffers(1, &m_VertexBuffer);

    struct Vertex
    {
        glm::vec2 Position;
        glm::vec2 TexCoord;
    };

    Vertex vertices[] = {
        { {-1.0f, -1.0f }, { 0.0f, 0.0f } },
        { { 3.0f, -1.0f }, { 2.0f, 0.0f } },
        { {-1.0f,  3.0f }, { 0.0f, 2.0f } }
    };

    glNamedBufferData(m_VertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(m_VertexArray, 0, m_VertexBuffer, 0, sizeof(Vertex));

    glEnableVertexArrayAttrib(m_VertexArray, 0);
    glEnableVertexArrayAttrib(m_VertexArray, 1);

    glVertexArrayAttribFormat(m_VertexArray, 0, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, Position)));
    glVertexArrayAttribFormat(m_VertexArray, 1, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(Vertex, TexCoord)));

    glVertexArrayAttribBinding(m_VertexArray, 0, 0);
    glVertexArrayAttribBinding(m_VertexArray, 1, 0);
}

AppLayer::~AppLayer()
{
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);

    glDeleteProgram(m_Shader);
}

void AppLayer::OnEvent(TM::Event &event)
{
    std::println("{}", event.ToString());

    TM::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<TM::WindowClosedEvent>([this](TM::WindowClosedEvent &e) {return OnWindowClosed(e);});
}

void AppLayer::OnUpdate(float ts)
{
    m_Time += ts;
}

void AppLayer::OnRender()
{
    glUseProgram(m_Shader);

    //Uniforms
    glUniform1f(0, m_Time);

    glm::vec2 framebufferSize = TM::Application::Get().GetFramebufferSize();
    glUniform2f(1, framebufferSize.x, framebufferSize.y);

    glViewport(0, 0, static_cast<GLsizei>(framebufferSize.x), static_cast<GLsizei>(framebufferSize.y));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(m_VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool AppLayer::OnWindowClosed(TM::WindowClosedEvent &event)
{
    std::println("Window Closed");

    return false;
}
