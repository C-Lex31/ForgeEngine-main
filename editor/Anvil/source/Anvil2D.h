#pragma once
#include "ForgeEngine.h"
#include"editor/scene_hierarchy_panel.h"
namespace Forge {
	class Anvil :public Layer
	{
	public:
		Anvil();
		virtual ~Anvil() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnUpdate(Timestep ts) override;
		virtual void OnGUIRender() override;
		void OnEvent(Event& event)override;


	private:
		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		void SerializeScene(FRef<Scene2d> scene, const std::filesystem::path& path);
	private:

		OrthographicCameraController m_CameraController;
		FRef<vertex_array> SQvertexArray;

		FRef<Scene2d>m_ActiveScene;

		FRef<shader> m_Shader;
		FRef<Texture2D>m_CheckerboardTexture, m_Logo;
		FRef<Framebuffer>m_Framebuffer;
		glm::vec2 m_ViewportSize ={0.0f,0.0f};
		glm::vec4 QuadColor1 = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec4 QuadColor2 = { 0.7f, 0.2f, 0.3f, 1.0f };

		bool OnViewportFocus =false;
		bool OnViewportHover = false;
		bool OnViewportDock = false;

		Entity QuadEntity;
		Entity CameraEntity;
		Entity CameraB;

		FRef<Scene2d> m_EditorScene;
		std::filesystem::path m_EditorScenePath;
		SceneHierarchyPanel m_SceneHierarchyPanel;

	};
}