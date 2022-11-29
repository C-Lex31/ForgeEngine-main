#include "frpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

namespace Forge {

	Camera::Camera(float width, float height, glm::vec3 Position)
		//:m_ProjectionMatrix(glm::ortho(left, right, bottom, up, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		//Camera::width = width;
	    //Camera::height = height;
		//Camera::m_Position = Position;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 
	}
	void Camera::SetProjection(float FOV, float aspectRatio)
	{
		m_fov = FOV;
		m_Aspect = aspectRatio;
	//	FR_TRACE("RESIZE {0}" ,m_fov);
		m_ProjectionMatrix = glm::perspective(glm::radians(m_fov), m_Aspect, 0.1f, 100.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		
    }

	void Camera::RecalculateViewMatrix(float nearPlane,float farPlane)
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Orientation, up);
		//FR_TRACE(m_fov);
		m_ProjectionMatrix = glm::perspective(glm::radians(m_fov), m_Aspect, nearPlane, farPlane);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 
	}


}