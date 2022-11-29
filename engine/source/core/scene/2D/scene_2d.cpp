#include "frpch.h"
#include "scene_2d.h"
#include "entity2d.h"
#include "components_2d.h"
#include "core/servers/rendering/renderer/Renderer2D.h"
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
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for (auto entity : group)
		{
			auto& [_transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad({ 0.0f,2.0f }, { 1.7f,0.5f }, sprite.m_Color);
		}

	}

}