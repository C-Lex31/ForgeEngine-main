#pragma once
#include "core/main/main.h"
#ifdef FR_PLATFORM_WINDOWS


extern Forge::Application* Forge::CreateApplication(ApplicationCommandLineArgs args);
int main(int argc, char** argv)
{
	Forge::Log::Init();
	FR_CORE_INFO("Initialized Log");
	FR_TRACE("READY");

	auto app = Forge::CreateApplication({ argc, argv });
//	printf(test);
	app->test_disp();
	app->Run();
	
	delete app;
}


#endif 
