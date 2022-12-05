#include"frpch.h"
#include"scene_hierarchy_panel.h"
#include"imgui.h"
#include"imgui_internal.h"
#include "core/scene/2D/components_2d.h"
#include <glm/gtc/type_ptr.hpp>
namespace Forge {
	SceneHierarchyPanel::SceneHierarchyPanel(const FRef<Scene2d>& scene)
	{
		SetContext(scene);
	}
	void SceneHierarchyPanel::SetContext(const FRef<Scene2d>& scene)
	{
		m_Context = scene;
	}
	void SceneHierarchyPanel::OnGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		
		m_Context->m_Registry.each([&](auto entityID)
		{
				Entity entity(entityID, m_Context.get());
				
			//auto& tc=entity.GetComponent<TagComponent>();
			//ImGui::Text("%s", tc.m_Tag.c_str());
			DrawEntityNode(entity);
		});
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext={};
		ImGui::End();

		ImGui::Begin("Details");
		if (m_SelectionContext.IsValid())
		{
		 DrawComponents(m_SelectionContext);
			
		}
		ImGui::End();



	}
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().m_Tag;
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened =ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}
		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		} 

	}
	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().m_Tag;

			char buffer[256]; //Max Tag name length
			memset(buffer, 0, sizeof(buffer)); //init buffer to 0
			strcpy_s(buffer, sizeof(buffer), tag.c_str()); //Copying the tag into buffer
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = FString(buffer);
			}
		
		}

		if (entity.HasComponent<TransformComponent>())
		{
			auto& transform = entity.GetComponent < TransformComponent>().m_Transform;
			ImGui::DragFloat3("Location", glm::value_ptr(transform[3]), 0.2f);
		}

	}
}
