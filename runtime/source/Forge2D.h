#pragma once
#include "ForgeEngine.h"

class Forge2D :public Forge::Layer
{
public:
	Forge2D();
	virtual ~Forge2D()=default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Forge::Timestep ts) override;
	virtual void OnGUIRender() override;
	void OnEvent(Forge::Event& event)override;
private:
	//Forge::orthographic_camera m_Cam2d;
	Forge::OrthographicCameraController m_Cam;
	Forge::FRef<Forge::vertex_array> SQvertexArray;

	Forge::FRef<Forge::shader> m_Shader;
//	Forge::FRef<Forge::Texture2D>m_CheckerboardTexture;

	glm::vec4 QuadColor1 = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 QuadColor2 = { 0.7f, 0.2f, 0.3f, 1.0f };
};
