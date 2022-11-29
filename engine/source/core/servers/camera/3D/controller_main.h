#pragma once

#include "camera.h"
#include "core/main/timestep.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/MouseEvents.h"

namespace Forge {

	class CameraController
	{
	public:
		CameraController(float AspectRatio, glm::vec3 position);//float width , float height ,glm::vec3 position);

		
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void ResizeBounds(float width, float height);
		


		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

	//	float GetZoomLevel() const { return m_ZoomLevel; }
		//void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio= 1.0f;

	
		Camera m_Camera;


	//	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	//	float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float CamTranslationSpeed = 0.0f;
		glm::vec3 m_Orientation = { 0.0f,0.0f,-1.0f };
		glm::vec3 Position  = {0,0,0};
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		bool firstMouse = true;

		float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		float pitch = 0.0f;
		float lastX = 1366.0 / 2.0;
		float lastY = 705.0 / 2.0;

		float fov = 45.0f;
	};

}
