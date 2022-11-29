//#include <iostream>
#include <ForgeEngine.h>
#include "platform/windows/winInput.h"
#include "Anvil2D.h"
#include "Anvil3D.h"
//#include "Forge3D.h"
//#include "GLFW/glfw3.h"
#include "core/client/entry_point.h"
namespace Forge {

	class ForgeEditor :public Application
	{
	public:
		ForgeEditor()
			:Application("Forge Editor")
		{
			//PushLayer(new Engine_Layer());
			PushLayer(new Anvil());
		}
		~ForgeEditor()
		{

		}

	};

	Application* CreateApplication()
	{
		return new ForgeEditor();
	}
}