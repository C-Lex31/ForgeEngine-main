//#include <iostream>
#include <ForgeEngine.h>
#include "platform/windows/winInput.h"
#include "Anvil2D.h"
#include "Anvil3D.h"

//#include "GLFW/glfw3.h"
#include "core/client/entry_point.h"
namespace Forge {

	class ForgeEditor :public Application
	{
	public:
		ForgeEditor(const ApplicationSpecification& spec)
			:Application( spec)
		{
			//PushLayer(new Engine_Layer());
			PushLayer(new Anvil());
		}
		

	};

	//Application* CreateApplication()
	//{
	//	return new ForgeEditor();
	//}
	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Anvil";
		spec.CommandLineArgs = args;

		return new ForgeEditor(spec);
	}
}