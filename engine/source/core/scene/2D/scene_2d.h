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
		//entt::registry& reg() { return m_Registry; } //TEMP
		void Scene2DUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
		friend class Entity;
	};


}