#include "frpch.h"
#include "scene_2d.h"
#include "entity2d.h"
#include "components_2d.h"
#include "core/servers/rendering/renderer/Renderer2D.h"
#include "scriptables.h"
namespace Forge {
	Scene2d::Scene2d()
	{
	}

	Scene2d::~Scene2d()
	{
	}
	Entity Scene2d::CreateEntity(const FString& TagName)
	{
		Entity entity(m_Registry.create(), this);
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.m_Tag = TagName.empty() ? "Default" : TagName;

		return entity;
	}

	void Scene2d::Scene2DUpdate(Timestep ts)
	{
		 {
		
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					// TODO: Move to Scene::OnScenePlay
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();
					}

					nsc.Instance->OnUpdate(ts);
				});
		}

		CameraCore* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{

			auto view= m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get < TransformComponent, CameraComponent>(entity);
				if (camera.isPrimary)
				{
					mainCamera = &camera.m_Camera;
					cameraTransform = &transform.m_Transform;
					break;
				}
				
			}
		}
		if (mainCamera){

			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for (auto entity : group)
			{
				auto& [_transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad({ 0.0f,2.0f }, { 1.7f,0.5f }, sprite.m_Color);
			}

			Renderer2D::EndScene();
	   }

	}

	void Scene2d::OnViewportResize(uint32_t width, uint32_t height)
	{
		

		if (m_ViewportWidth == width && m_ViewportHeight == height)
			return;

		m_ViewportWidth = width;
		m_ViewportWidth = height;
		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.m_Camera.SetViewportSize(width, height);
		}
	}

}