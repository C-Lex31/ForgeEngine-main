#pragma once

#include "orthographic_camera.h"
#include "core/main/timestep.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/MouseEvents.h"

namespace Forge {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void ResizeBounds(float width, float height);

		
		orthographic_camera& GetCamera() { return m_Camera; }
		const orthographic_camera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		orthographic_camera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 0.0f, m_CameraRotationSpeed = 180.0f;
	};

}