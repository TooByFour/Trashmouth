#include <Trashmouth/Core/Application.h>

#include "AppLayer.h"

int main()
{
    TM::ApplicationSpecification appSpec;
    appSpec.Name = "Sandbox";
    appSpec.WindowSpecification.Width = 1920;
    appSpec.WindowSpecification.Height = 1080;

    TM::Application application(appSpec);
    application.PushLayer<AppLayer>();
    application.Run();
}