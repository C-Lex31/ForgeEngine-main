#include "Forge3D.h"
#include "ForgeEngine.h"

Forge3D::Forge3D()
	:Layer("Forge3D"), m_Cam(1366/705, { 0, 0, 1 })
{
}

void Forge3D::OnAttach()
{
	//m_Texture2D = Forge::Texture2D::create("assets/textures/brick.png");
	m_PlankTexture= Forge::Texture2D::create("assets/textures/planks.png",0);
//	m_PlankTexture2= Forge::Texture2D::create("assets/textures/planks.png", 0, "");
	m_PlankSpecular = Forge::Texture2D::create("assets/maps/PlanksSpec.png",1);
}

void Forge3D::OnDetach()
{
}

void Forge3D::OnUpdate(Forge::Timestep ts)
{
	
	m_Cam.OnUpdate(ts);
	
	
	Forge::render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
	Forge::render_commands::clear();

	Forge::Renderer3D::BeginScene(m_Cam.GetCamera());

	//Forge::Renderer3D::DrawPyramid({-0.0f,-0.49f,-0.1f}, {0.6f,0.6f,0.6f},m_Texture2D,LightColor,LightPos);
	Forge::Renderer3D::DrawPlane({0.0f,-0.5f,0.0f}, {5.0f,0.0f,5.0f},m_PlankTexture, m_PlankSpecular,LightColor,LightPos);
	//Forge::Renderer3D::DrawCube({ 1.0f,0.0f,0.0f }, { 0.2f,0.2f,0.2f }, CubeColor);
	Forge::Renderer3D::DrawCube(LightPos, { 0.3f,0.3f,0.3f }, LightColor);
	Forge::Renderer3D::EndScene();
}

void Forge3D::OnGUIRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Cube Color", glm::value_ptr(CubeColor));
	ImGui::End();
}

void Forge3D::OnEvent(Forge::Event& event)
{
}
