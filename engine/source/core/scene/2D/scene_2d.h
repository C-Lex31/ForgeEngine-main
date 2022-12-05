#pragma once


#include "entt.hpp"
#include "core/main/timestep.h"

namespace Forge {

	class Entity;
	class Scene2d
	{
	public:
		Scene2d();
		~Scene2d();

		Entity CreateEntity(const FString& TagName = "");
		void DestroyEntity(Entity en);
		//entt::registry& reg() { return m_Registry; } //TEMP
		void Scene2DUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		friend class Entity;
		friend class SceneHierarchyPanel;
	};


}