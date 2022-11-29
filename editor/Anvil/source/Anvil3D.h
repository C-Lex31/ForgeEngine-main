#pragma once
#include "ForgeEngine.h"

namespace Forge {
	class Anvil3D :public Layer
	{
	public:
		Anvil3D();
		virtual ~Anvil3D() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnUpdate(Timestep ts) override;
		virtual void OnGUIRender() override;
		void OnEvent(Event& event)override;
	private:
		CameraController m_CamController;
		//Camera m_Cam;
		FRef<vertex_array> m_vertexArray;
		FRef<Texture2D>m_Texture2D;
		FRef<Texture2D>m_PlankTexture;
		FRef<Texture2D>m_PlankTexture2;
		FRef<Texture2D>m_PlankSpecular;
		FRef<Framebuffer>m_Framebuffer;
		glm::vec4 CubeColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		glm::vec4 LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 LightPos = glm::vec3(-0.2f, 0.1f, -0.1f);

		glm::vec2 m_ViewportSize = { 0.0f,0.0f };
		bool OnViewportFocus = false;
		bool OnViewportHover = false;
		bool OnViewportDock = false;

		short AvoidHoverCheckFlag = 0;
	};
}