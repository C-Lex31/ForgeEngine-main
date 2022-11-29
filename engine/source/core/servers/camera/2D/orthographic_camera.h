#pragma once

#include <glm/glm.hpp>

namespace Forge {

	class orthographic_camera
	{
	public:
		orthographic_camera(float left, float right, float bottom, float up);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetCamPos() { return m_Position; }
		void SetCamPos(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const float  GetCamRot() { return m_Rotation; }
		void SetCamRot(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		//void OrthographicCameraInput(float sec);
	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };//sadly glm does not auto initialize stuff :(
		float m_Rotation = 0.0f;
		glm::vec3 m_cam2dPos ={ 0.0f, 0.0f, 0.0f};
		float m_cam2dRot=0.0f;
		float m_cam2dMoveSpeed = 3.0f;
		float m_cam2dRotSpeed = 180.0f;
		float rotation = 0.0f;
	};

}
