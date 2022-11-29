#include "Forge2D.h"


Forge2D::Forge2D()
	:Layer("Forge2D"), m_Cam(1366/707,true)
{

}

void Forge2D::OnAttach()
{
//	m_CheckerboardTexture = Forge::Texture2D::create("assets/textures/Checkerboard.png");
	//m_Logo = Forge::Texture2D::create("assets/textures/AwesomeFace.png",1);
    
}

void Forge2D::OnDetach()
{
}

void Forge2D::OnUpdate(Forge::Timestep ts)
{
	//--------------------------------------------------2D Camera------------------------------------------------------------------------------------------------------
	//m_Cam2d.OrthographicCameraInput(ts.GetSec());
	m_Cam.OnUpdate(ts.GetSec());
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

    Forge::render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
	Forge::render_commands::clear();


    Forge::Renderer2D::BeginScene(m_Cam.GetCamera());
	//Forge::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.7f,0.5f }, QuadColor1);
//	Forge::Renderer2D::DrawQuad({ 1.0f,0.0f }, { 0.8f,0.5f }, QuadColor2);
	//Forge::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f,1.0f }, m_Logo);

//	Forge::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 5.0f,5.0f }, m_CheckerboardTexture , m_Logo);
	
//	Forge::Renderer2D::EndScene();

}

void Forge2D::OnGUIRender()
{
   // ImGui::Begin("Settings");
   // ImGui::ColorEdit4("Quad Color 1", glm::value_ptr(QuadColor1));
   // ImGui::ColorEdit4("Quad Color 2", glm::value_ptr(QuadColor2));
   // ImGui::End();
   ImGui::Begin("Settings");
    ImGui::ColorEdit4("Quad Color 1", glm::value_ptr(QuadColor1));
    ImGui::ColorEdit4("Quad Color 2", glm::value_ptr(QuadColor2));
   
    ImGui::End();

}

void Forge2D::OnEvent(Forge::Event& event)
{
	m_Cam.OnEvent(event);
}


