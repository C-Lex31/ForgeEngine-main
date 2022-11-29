#include "frpch.h"

#include "editor_interface.h"
//#include <imgui.h>
#include "core/main/main.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
namespace Forge {

	UI_Layer::UI_Layer()
		:Layer("Base_Layer")
	{

	}
	
	void UI_Layer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();									//ImGui----->ForgeUI
		ImGuiIO& io = ImGui::GetIO(); (void)io;					//ImGuiIO--->FListenIO
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//	io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Gui style
		//ImGui::StyleColorsDark();
		ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();						//ImGuiStyle--->FStyle
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
		
	
		
	}
	void UI_Layer::OnDetach()
	{

	}
	void UI_Layer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void UI_Layer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& is = Application::Get();
	//	io.AddMouseWheelEvent()
		io.DisplaySize = ImVec2((float)is.GetWindow().GetWidth(), (float)is.GetWindow().GetHeight());
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}


	}

	

	void UI_Layer::OnGUIRender()
	{
	//	static bool show = true;
	//	ImGui::ShowDemoWindow(&show);
		
	}

	void UI_Layer::OnEvent(Event& e)
	{
		
		
		if (m_EventLock)
		{
			ImGuiIO& io = ImGui::GetIO();
		//	EventDispatcher dispatcher(e);
		//	dispatcher.Dispatch<MouseScrolledEvent>(FR_BIND_EVENT_FN(UI_Layer::OnMouseScrolledEvent));
			//io.WantCaptureKeyboard;
			e.m_handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.m_handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard; 
		//	FR_TRACE( e.m_handled);
		}
		

	}
	
	bool UI_Layer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//i//o.MouseWheel += e.GetYOffset();
		//FR_TRACE("enter");
		return false;
	}




}
