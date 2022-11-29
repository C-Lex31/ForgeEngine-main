#pragma once

#ifdef FR_PLATFORM_WINDOWS

//extern Iris::Application* Iris::CreateApplication();

int main(int argc, char** argv)
{
	Forge::Log::Init();
	FR_CORE_INFO("Initialized Log");
	FR_TRACE("READY");

	Forge::Application* app = Forge::CreateApplication();
//	printf(test);
	app->test_disp();
	app->Run();
	
	delete app;
}


#endif 
