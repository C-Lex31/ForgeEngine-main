#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
namespace Forge {

	class Camera
	{
	public:
		Camera(float width, float height, glm::vec3 position);


		void SetProjection(float FOV, float aspectRatio);
		void SetCamPosition(const glm::vec3& position  ) { m_Position = position; RecalculateViewMatrix(); }
		void SetCamOrientation(glm::vec3 orientation) { m_Orientation = orientation; RecalculateViewMatrix(); }

		const glm::vec3& GetCamPos() const { return m_Position; }

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const {  return m_ViewProjectionMatrix; }


		void RecalculateViewMatrix( float nearPlane=0.1f, float farPlane=100.0f);
		
	private:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix=glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);
		
		glm::vec3 m_Position ={0.0,0.0,0.0};               //To use these components in ForgeEngine.cpp unit make them public and inline static
		glm::vec3 m_Orientation = { 0.0f,0.0f,0.0f };
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		
		float width;
		float height;
		float m_fov =1.0f;
		float m_Aspect =1.0f;
	};

}
