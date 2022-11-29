#include "frpch.h"
#include "orthographic_camera.h"
#include "core/input/input.h"
#include "core/input/keycodes.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Forge {

	orthographic_camera::orthographic_camera(float left, float right, float bottom, float up)
		:m_ProjectionMatrix(glm::ortho(left,right,bottom,up,-1.0f,1.0f)),m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 
	}

	void orthographic_camera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	/*void orthographic_camera::OrthographicCameraInput(float sec)
	{
		if (input::isKeyPressed(FR_KEY_A))
			m_cam2dPos.x -= m_cam2dMoveSpeed * sec;
		else if (input::isKeyPressed(FR_KEY_D))
			m_cam2dPos.x += m_cam2dMoveSpeed * sec;
		if (input::isKeyPressed(FR_KEY_W))
			m_cam2dPos.y += m_cam2dMoveSpeed * sec;
		else if (input::isKeyPressed(FR_KEY_S))
			m_cam2dPos.y -= m_cam2dMoveSpeed * sec;

		if (input::isKeyPressed(FR_KEY_Q))
			m_cam2dRot += m_cam2dRotSpeed * sec;

		else if (input::isKeyPressed(FR_KEY_E))
			m_cam2dRot -= m_cam2dRotSpeed * sec;

		SetCamPos(m_cam2dPos);
		SetCamRot(m_cam2dRot);
	}*/

	void orthographic_camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
							  glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 
	}


}