#pragma once
#include "glm/glm.hpp"

namespace Forge {

	struct TagComponent
	{
		FString m_Tag;
		TagComponent() = default;
		TagComponent(const FString& TagName)
			:m_Tag(TagName) {}
	};
	struct TransformComponent
	{
		glm::mat4 m_Transform{1.0f};
		TransformComponent() = default;
		TransformComponent(const glm::mat4& transform)
			:m_Transform(transform) {}

		operator  glm::mat4()  { return m_Transform; }
		operator const glm::mat4() const { return m_Transform; }

	};

	struct SpriteRendererComponent
	{
		glm::vec4 m_Color{1.0f,1.0f,1.0f,1.0f};
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const glm::vec4& color)
			:m_Color(color) {}
		operator const glm::vec4() const { return m_Color; }
	};

}
