#pragma once

#include "core/core.h"
#include "core/Events/EventRegister.h"
#include "timestep.h"

#include "platform/windows/windows.h"
#include "core/layers/layerStack.h"
#include "core/editor/editor_interface.h"
#include "core/servers/rendering/core_rd/buffers.h"
#include "core/servers/rendering/core_rd/vertex_array.h"
#include "core/servers/rendering/core_rd/shader.h"

int main(int argc, char** argv);
namespace Forge {

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			FR_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Forge Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};


	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		UI_Layer* get_ui_layer() { return m_guiLayer; }
	    Window& GetWindow() { return *m_Window; }
		void Close();
		static Application& Get() { return *s_Instance; }
		void test_disp() { printf("Test Pass"); }
		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

	private:
		bool OnWindowResize(WindowResizeEvent& e);
		//Close event
	
	private:
	    FScope<Window> m_Window;
		UI_Layer* m_guiLayer;
		float m_LastFrameTime = 0.0f;
		bool m_running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		ApplicationSpecification m_Specification;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};
	//Defined in client
	Application* CreateApplication(ApplicationCommandLineArgs args);
	
}