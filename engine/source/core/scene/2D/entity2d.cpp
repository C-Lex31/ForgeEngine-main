#include "frpch.h"
#include "entity2d.h"

namespace Forge {
	Entity::Entity(entt::entity en, Scene2d* scn)
		:m_EntityHandle(en) , m_Scene(scn)
	{

	}
}
