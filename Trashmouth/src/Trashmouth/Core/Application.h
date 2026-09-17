#include "Event.h"
#include "Layer.h"
#include <Trashmouth/tmpch.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <concepts>
#include "Window.h"

namespace TM {
    struct ApplicationSpecification
    {
        std::string Name = "Application";
        WindowSpecification WindowSpecification;
    };

class Application {
public:
  Application(const ApplicationSpecification &spec);
  ~Application();

  void Run();
  void Stop();

  void RaiseEvent(Event &event);

  template<typename TLayer>
  requires(std::derived_from<TLayer, Layer>)
  void PushLayer()
  {
      m_LayerStack.push_back(std::make_unique<TLayer>());
  }
  Layer *getLayer();

  static Application &Get();
  std::shared_ptr<Window> GetWindow() const
  {
      return m_Window;
  }

  glm::vec2 GetFramebufferSize() const;
  float GetTime();

private:
  std::vector<std::unique_ptr<Layer>> m_LayerStack;
  bool m_Running = false;
  std::shared_ptr<Window> m_Window;
  ApplicationSpecification m_Specification;

  friend class Layer;
};
} // namespace TM
