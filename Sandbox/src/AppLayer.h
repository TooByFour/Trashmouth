#pragma once

#include "Trashmouth/Core/Layer.h"
#include "Trashmouth/Core/WindowEvents.h"

#include "glm/glm.hpp"
#include <cstdint>
#include <stdint.h>

class AppLayer : public TM::Layer
{
    public:
        AppLayer();
        virtual ~AppLayer();

        virtual void OnEvent(TM::Event &event) override;

        virtual void OnUpdate(float ts) override;
        virtual void OnRender() override;

    private:
        bool OnWindowClosed(TM::WindowClosedEvent &event);

    private:
        uint32_t m_Shader = 0;
        uint32_t m_VertexArray = 0;
        uint32_t m_VertexBuffer = 0;

        float m_Time = 0.0f;
};
