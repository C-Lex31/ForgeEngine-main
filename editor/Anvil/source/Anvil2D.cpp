#include "Anvil2D.h"

namespace Forge {

	Anvil::Anvil()
		:Layer("Forge2D"),m_CameraController(1366/705,true)
	{

	}

	void Anvil::OnAttach()
	{

        m_CheckerboardTexture = Texture2D::create("assets/textures/Checkerboard.png", 0);
        //m_Logo = Texture2D::create("assets/textures/AwesomeFace.png",1);
        FramebufferSpecs FSpec;
        FSpec.width = 1366;
        FSpec.height = 705;
        m_Framebuffer = Framebuffer::create(FSpec);
        m_ActiveScene = FCreateRef<Scene2d>();

      QuadEntity=  m_ActiveScene->CreateEntity("Quad");


      QuadEntity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f,1.0f,0.0f,1.0f });  
    
      CameraEntity = m_ActiveScene->CreateEntity("Main Camera");
      CameraEntity.AddComponent<CameraComponent>();

      CameraB = m_ActiveScene->CreateEntity("CameraB");
      auto& Cam2 = CameraB.AddComponent<CameraComponent>();
      Cam2.isPrimary = false;

    //  CameraEntity.AddComponent<NativeScriptComponent>();
      //ClipSpaceCamera.AddComponent<NativeScriptComponent>();

      class CameraController :public ScriptableEntity
      {
      public:
          void OnCreate()
          {

          }
          void OnDestroy()
          {
            
          }
          void OnUpdate(Timestep ts)
          {
              FR_TRACE("Timestep :{0}", ts.GetSec());
              auto& transform = GetComponent<TransformComponent>().m_Transform;
              float speed = 5.0f;
              if (input::isKeyPressed(KeyCode::A))
                  transform[3][0] -= speed *ts.GetSec();
          }

      };

      CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
      m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

	void Anvil::OnDetach()
	{
	}

	void Anvil::OnUpdate(Timestep ts)
	{
        m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

        if (FramebufferSpecs spec = m_Framebuffer->GetFramebufferSpecs();
            m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
            (spec.width != m_ViewportSize.x || spec.height != m_ViewportSize.y))
        {
            m_Framebuffer->resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_CameraController.ResizeBounds(m_ViewportSize.x, m_ViewportSize.y);
        }
        //--------------------------------------------------2D Camera------------------------------------------------------------------------------------------------------
      // m_Cam2d.OrthographicCameraInput(ts.GetSec());
    //    FR_TRACE((!OnViewportDock && OnViewportFocus) || (OnViewportDock && OnViewportFocus));
        if ((!OnViewportDock && OnViewportFocus) || (OnViewportDock && OnViewportFocus))
        {
            m_CameraController.OnUpdate(ts);
        
        }
        //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
        m_Framebuffer->bind();
        render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
        render_commands::clear();

      

     //   Renderer2D::BeginScene(m_CameraController.GetCamera());
       
     //   Renderer2D::DrawQuad({ 0.0f,2.0f }, { 1.7f,0.5f }, QuadColor1);
      //  Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.8f,0.5f }, QuadColor2);
      //  Renderer2D::DrawTRSQuad({ -1.0f,0.0f }, { 1.0f,1.0f },20, QuadColor2);
    //   Renderer2D::DrawQuad({ 0.0f,0.0f }, { 10.0f,10.0f }, m_CheckerboardTexture,3);
        m_ActiveScene->Scene2DUpdate(ts);
       // Renderer2D::DrawQuad({ 0.0f,0.0f }, { 5.0f,5.0f }, m_CheckerboardTexture, m_Logo);

    //    Renderer2D::EndScene();
        m_Framebuffer->unbind();

	}

	void Anvil::OnGUIRender()
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

        m_SceneHierarchyPanel.OnGuiRender();
      //  ImGui::Begin("Settings");
        
      //  m_ActiveScene->reg().get<SpriteRendererComponent>(QuadEntity)
      //  if (QuadEntity.IsValid()) {
       //     auto& QuadColor = QuadEntity.GetComponent<SpriteRendererComponent>().m_Color;
       //     ImGui::ColorEdit4("Quad Color 1", glm::value_ptr(QuadColor));
            //  ImGui::ColorEdit4("Quad Color 2", glm::value_ptr(QuadColor2));
       // }
   //     ImGui::End();
       
        ImGui::Begin("Scene View");
        ImGuiBackendFlags backend_flags = io.BackendFlags;
        ImGui::Checkbox("io.ConfigViewportsNoAutoMerge", &io.ConfigViewportsNoAutoMerge);
      //  ImGui::CheckboxFlags("io.ConfigFlags: ViewportsEnable", &io.ConfigFlags, ImGuiConfigFlags_ViewportsEnable);
      //  ImGui::CheckboxFlags("io.BackendFlags: HasMouseHoveredViewport", &backend_flags, ImGuiBackendFlags_HasMouseHoveredViewport);
     //   ImGui::Checkbox("io.ConfigDockingTransparentPayload", &io.ConfigDockingTransparentPayload);
      //  ImGui::CheckboxFlags("io.BackendFlags: PlatformHasViewports", &backend_flags, ImGuiBackendFlags_PlatformHasViewports);
    //  backend_flags=  ImGuiBackendFlags_HasMouseHoveredViewport;
    //  io.ConfigDockingTransparentPayload =true;
      //backend_flags= ImGuiBackendFlags_PlatformHasViewports;
        OnViewportFocus = ImGui::IsWindowFocused();
        OnViewportDock = ImGui::IsWindowDocked();
        OnViewportHover = ImGui::IsWindowHovered();
        

      //  if ((OnViewportDock && !(OnViewportFocus)) || (!OnViewportDock && (!OnViewportFocus ))  )
     //   {
        //    FR_TRACE("enter");
          //  Application::Get().get_ui_layer()->InitiateEventLock(true );
           
      //  }
        if ((OnViewportDock && !(OnViewportFocus)) || (!OnViewportDock && !OnViewportFocus) || !OnViewportHover )
        {
            Application::Get().get_ui_layer()->InitiateEventLock(true);
        }
      //  else if ((OnViewportDock && OnViewportFocus)|| (!OnViewportDock && OnViewportFocus) || (OnViewportHover && !OnViewportFocus ) )
        if ((OnViewportFocus&& OnViewportHover) || OnViewportHover)

        {

           Application::Get().get_ui_layer()->InitiateEventLock(false);
        }
     
        ImVec2 ViewportPanelSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != *(glm::vec2*)& ViewportPanelSize) //--->Casting memory address of VPS to glm vec 2 ptr and then derefrencing
        {

            
            m_ViewportSize = { ViewportPanelSize.x,ViewportPanelSize.y };
         //   m_Framebuffer->resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_CameraController.ResizeBounds(ViewportPanelSize.x, ViewportPanelSize.y);
        }
       // FR_TRACE("Viewport :{0},{1}", ViewportPanelSize.x, ViewportPanelSize.y);
        uint32_t TexID = m_Framebuffer->GetColorAttachmentID();
        ImGui::Image((void*)TexID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();  ///End Scene View

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::End(); ///Shutdown Docker
	}

	void Anvil::OnEvent(Event& event)
	{
       
        m_CameraController.OnEvent(event);
      //  if ((!OnViewportDock && OnViewportFocus) || (OnViewportDock && OnViewportFocus))
        // event.m_handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
	}

}