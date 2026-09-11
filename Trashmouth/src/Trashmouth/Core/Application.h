#include <Trashmouth/Core/Event>
#include <Trashmouth/Core/Layer>
#include <Trashmouth/tmpch.h>
#include <vendor/glm/glm.hpp>

namespace TM {
class Application {
public:
  Application();
  ~Application() = default;

  void Run();
  void Stop();

  void RaiseEvent(Event &event);

  void PushLayer(Layer L);
  Layer *getLayer();

  static Application Get();

private:
  vector<std::unique_ptr<Layer>> Layerstack;
  bool m_Running = false;

  friend class Layer;
};
} // namespace TM
