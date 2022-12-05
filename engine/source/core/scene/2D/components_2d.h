#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "core/servers/camera/CameraCore.h"
#include "scene2d_camera.h"
#include "scriptables.h"
namespace Forge {

	struct TagComponent
	{
		FString m_Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const FString& TagName)
			:m_Tag(TagName) {}
	};
	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		glm::mat4 m_Transform{1.0f};
		TransformComponent() = default;
		TransformComponent(const glm::mat4& transform)
			:m_Transform(transform) {}

		operator  glm::mat4()  { return m_Transform; }
		operator const glm::mat4() const { return m_Transform; }

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}

	};

	struct SpriteRendererComponent
	{
		glm::vec4 m_Color{1.0f,1.0f,1.0f,1.0f};
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const glm::vec4& color)
			:m_Color(color) {}
		//operator const glm::vec4() const { return m_Color; }
	};

	struct CameraComponent
	{
		Forge::SceneCamera m_Camera;

		bool isPrimary = true;
		bool FixedAspectRatio = false;
		CameraComponent() = default;
	//	CameraComponent(const glm::mat4& projection)
	//		:m_Camera(projection) {};
	};

	class ScriptableEntity;
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};


}
