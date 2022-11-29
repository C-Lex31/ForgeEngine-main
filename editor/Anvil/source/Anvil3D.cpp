#include "Anvil3D.h"


namespace Forge {
	Anvil3D::Anvil3D()
		:Layer("Anvil"), m_CamController(1366/705,{0,0,2})
	{
	}

	void Anvil3D::OnAttach()
	{
		m_Texture2D = Texture2D::create("assets/textures/brick.png");
		m_PlankTexture = Texture2D::create("assets/textures/planks.png", 0);
		//	m_PlankTexture2= Texture2D::create("assets/textures/planks.png", 0, "");
		m_PlankSpecular = Texture2D::create("assets/maps/PlanksSpec.png", 1);

		FramebufferSpecs FSpec;
		FSpec.width = 1366;
		FSpec.height = 705;
		m_Framebuffer = Framebuffer::create(FSpec);
	}

	void Anvil3D::OnDetach()
	{
	}

	void Anvil3D::OnUpdate(Timestep ts)
	{


        if ((!OnViewportDock && OnViewportFocus) || (OnViewportDock && OnViewportFocus) )
            m_CamController.OnUpdate(ts);


		m_Framebuffer->bind();
		render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
		render_commands::clear();

		Renderer3D::BeginScene(m_CamController.GetCamera() );

	//	Renderer3D::DrawPyramid({-0.0f,-0.49f,-0.1f}, {0.6f,0.6f,0.6f},m_Texture2D,LightColor,LightPos);
		Renderer3D::DrawPlane({ 0.0f,-0.5f,0.0f }, { 5.0f,0.0f,5.0f }, m_PlankTexture, m_PlankSpecular, LightColor, LightPos);
		Renderer3D::DrawCube({ 1.0f,0.0f,0.0f }, { 0.2f,0.2f,0.2f }, CubeColor);
		Renderer3D::DrawCube(LightPos, { 0.3f,0.3f,0.3f }, LightColor);
		Renderer3D::EndScene();

		m_Framebuffer->unbind();
	}

	void Anvil3D::OnGUIRender()
	{
      static bool OnDockspace = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace ", &OnDockspace, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }


        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("Quit")) { Application::Get().Close(); }


                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }
        ImGui::Begin("Settings");

        ImGui::ColorEdit4("Cube Color", glm::value_ptr(CubeColor));
        ImGui::End();

        ImGui::Begin("Scene View");
        ImGuiBackendFlags backend_flags = io.BackendFlags;
      //  ImGui::Checkbox("io.ConfigViewportsNoAutoMerge", &io.ConfigViewportsNoAutoMerge);
        //  ImGui::CheckboxFlags("io.ConfigFlags: ViewportsEnable", &io.ConfigFlags, ImGuiConfigFlags_ViewportsEnable);
        //  ImGui::CheckboxFlags("io.BackendFlags: HasMouseHoveredViewport", &backend_flags, ImGuiBackendFlags_HasMouseHoveredViewport);
       //   ImGui::Checkbox("io.ConfigDockingTransparentPayload", &io.ConfigDockingTransparentPayload);
        //  ImGui::CheckboxFlags("io.BackendFlags: PlatformHasViewports", &backend_flags, ImGuiBackendFlags_PlatformHasViewports);
      //  backend_flags=  ImGuiBackendFlags_HasMouseHoveredViewport;
      //  io.ConfigDockingTransparentPayload =true;
        //backend_flags= ImGuiBackendFlags_PlatformHasViewports

        bool isRightMouse = input::isMouseButtonPressed(Mouse::Button1);
        OnViewportDock = ImGui::IsWindowDocked();
        OnViewportHover = ImGui::IsWindowHovered();

        if (input::isMouseButtonPressed(Mouse::Button1) && AvoidHoverCheckFlag == 0)
        {
            if (OnViewportHover)
            {
                OnViewportFocus = true;
                AvoidHoverCheckFlag = 1;
            }
        }
        else if (!input::isMouseButtonPressed(Mouse::Button1))
        {
            OnViewportFocus = ImGui::IsWindowFocused();
            AvoidHoverCheckFlag = 0;
        }
      
        
        if ((OnViewportDock && !(OnViewportFocus)) || (!OnViewportDock && !OnViewportFocus) || !OnViewportHover ||isRightMouse)
        {
            Application::Get().get_ui_layer()->InitiateEventLock(true);
        }
       
        if ((OnViewportFocus && OnViewportHover) || OnViewportHover)

        {
           Application::Get().get_ui_layer()->InitiateEventLock(false);
        }

        ImVec2 ViewportPanelSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != *(glm::vec2*)&ViewportPanelSize) //--->Casting memory address of VPS to glm vec 2 ptr and then derefrencing
        {
            m_ViewportSize = { ViewportPanelSize.x,ViewportPanelSize.y };
            m_Framebuffer->resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_CamController.ResizeBounds(ViewportPanelSize.x, ViewportPanelSize.y);
        }
       // FR_TRACE("Viewport :{0},{1}", ViewportPanelSize.x, ViewportPanelSize.y);
        uint32_t TexID = m_Framebuffer->GetColorAttachmentID();
        ImGui::Image((void*)TexID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();  ///End Scene View

        ImGui::End(); //Close Docker

	}

	void Anvil3D::OnEvent(Event& event)
	{
        m_CamController.OnEvent(event);
	}
}