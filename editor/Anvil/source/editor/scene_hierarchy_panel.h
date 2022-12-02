#pragma once

#include "core/core.h"
#include "core/scene/2D/scene_2d.h"
#include "core/scene/2D/entity2d.h"

namespace Forge {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const FRef<Scene2d>& scene);

		void SetContext(const FRef<Scene2d>& scene);

		void OnGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		template<typename T>
		void DisplayAddComponentEntry(const std::string& entryName);

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		FRef<Scene2d> m_Context;
		Entity m_SelectionContext;
	};

}