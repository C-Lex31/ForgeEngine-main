#pragma once
#include <glm/glm.hpp>

namespace Forge {

	class CameraCore
	{
	public:
		CameraCore() = default;
		CameraCore(const glm::mat4& projection)
			:m_ProjectionMatrix(projection) {}

		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }
	protected:
		glm::mat4 m_ProjectionMatrix;
	};
}