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

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Game Object"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}
		ImGui::End();

		ImGui::Begin("Details");
		if (m_SelectionContext.IsValid())
		{
		 DrawComponents(m_SelectionContext);

		 ImGui::SameLine();
		 ImGui::PushItemWidth(-1);

		 if (ImGui::Button("Add Component"))
			 ImGui::OpenPopup("AddComponent");

		 if (ImGui::BeginPopup("AddComponent"))
		 {
			 DisplayAddComponentEntry<CameraComponent>("Camera");
			 //		DisplayAddComponentEntry<ScriptComponent>("Script");
			 DisplayAddComponentEntry<SpriteRendererComponent>("Sprite Renderer");
			 //		DisplayAddComponentEntry<CircleRendererComponent>("Circle Renderer");
			 //		DisplayAddComponentEntry<Rigidbody2DComponent>("Rigidbody 2D");
			 //		DisplayAddComponentEntry<BoxCollider2DComponent>("Box Collider 2D");
			 //		DisplayAddComponentEntry<CircleCollider2DComponent>("Circle Collider 2D");

			 ImGui::EndPopup();
		 }
		 ImGui::PopItemWidth();
			
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

		bool LocalEntityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete GameObject"))
				LocalEntityDeleted = true;  //Deferring Deletion for safe destruction of entity

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		} 

		if (LocalEntityDeleted) {
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 120.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5,5});

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.3f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.3f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.3f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
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
			auto& transform = entity.GetComponent < TransformComponent>();
			DrawVec3Control("Translation", transform.Translation);

			glm::vec3 rotationInDeg = glm::degrees(transform.Rotation);
			DrawVec3Control("Rotation", rotationInDeg);
			transform.Rotation = glm::radians(rotationInDeg);

			DrawVec3Control("Scale", transform.Scale);
			ImGui::DragFloat3("Location", glm::value_ptr(transform.Translation), 0.2f);
		}
		if (entity.HasComponent<CameraComponent>())
		{
			auto& cameraComponent = entity.GetComponent < CameraComponent>().m_Camera;

			ImGui::Checkbox("bIsPrimary", &entity.GetComponent < CameraComponent>().isPrimary);
			const char* ProjectionTypeStrings[] = { "Perspective" , "Orthographic" };
			const char* CurrentProjectionTypeString = ProjectionTypeStrings[(int)cameraComponent.GetProjectionType()];//casting enum to int
			if (ImGui::BeginCombo("Projection", CurrentProjectionTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool selected = CurrentProjectionTypeString == ProjectionTypeStrings[i];
					if (ImGui::Selectable(ProjectionTypeStrings[i], selected))
					{
						CurrentProjectionTypeString = ProjectionTypeStrings[i];
						cameraComponent.SetProjectionType((SceneCamera::ProjectionType)i);//casting int back to enum
					}
					if (selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (cameraComponent.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				float orthograhicSize = cameraComponent.GetOrthographicSize();
				if (ImGui::DragFloat("OrthographicSize", &orthograhicSize))
					cameraComponent.SetOrthographicSize(orthograhicSize);

				float orthograhicNear = cameraComponent.GetOrthographicNearClip();
				if (ImGui::DragFloat("NearClip", &orthograhicNear))
					cameraComponent.SetOrthographicNearClip(orthograhicNear);

				float orthograhicFar = cameraComponent.GetOrthographicFarClip();
				if (ImGui::DragFloat("FarClip", &orthograhicFar))
					cameraComponent.SetOrthographicFarClip(orthograhicFar);
			}
			if (cameraComponent.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				float verticalFOV = glm::degrees(cameraComponent.GetPerspectiveVerticalFOV());
				if (ImGui::DragFloat("OrthographicSize", &verticalFOV))
					cameraComponent.SetPerspectiveVerticalFOV(glm::radians(verticalFOV));

				float orthograhicNear =  cameraComponent.GetPerspectiveNearClip();
				if (ImGui::DragFloat("NearClip", &orthograhicNear))
					cameraComponent.SetPerspectiveNearClip(orthograhicNear);

				float orthograhicFar = cameraComponent.GetPerspectiveFarClip();
				if (ImGui::DragFloat("FarClip", &orthograhicFar))
					cameraComponent.SetPerspectiveFarClip(orthograhicFar);
				
			}
		}


		if (entity.HasComponent<SpriteRendererComponent>())
		{
			auto& spriteRenderer= entity.GetComponent <SpriteRendererComponent>();
			ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer.m_Color));
			
		}

	}
	template<typename T>
	void SceneHierarchyPanel::DisplayAddComponentEntry(const std::string& entryName) {
		if (!m_SelectionContext.HasComponent<T>())
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				m_SelectionContext.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}
}
