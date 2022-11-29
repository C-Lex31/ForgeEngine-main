#pragma once
#include "scene_2d.h"
#include "entt.hpp"

namespace Forge {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity en , Scene2d* scn );

		template<typename T ,typename... Args>
		T& AddComponent(Args&&... args)
		{
			FR_CORE_ASSERT(!HasComponent<T>(), "Entity already has the component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);//Forwarding the args to entt instead of unpacking here
		}

		template<typename T>
		T& GetComponent()
		{
			FR_CORE_ASSERT(HasComponent<T>(), "Entity does not have the component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}
		template<typename T>
		void RemoveComponent()
		{
			FR_CORE_ASSERT(HasComponent<T>(), "Entity does not have the component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

	private:
		entt::entity m_EntityHandle;
		Scene2d* m_Scene;
	};


}