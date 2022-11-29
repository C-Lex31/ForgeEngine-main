#include "frpch.h"
#include "controller.h"

#include "core/input/input.h"
#include "imgui.h"
#include "core/input/keycodes.h"

namespace Forge {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
	

		if (input::isKeyPressed(KeyCode::A) || ImGui::IsKeyDown(KeyCode::A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts.GetSec();
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts.GetSec();
		}
		else if (input::isKeyPressed(KeyCode::D) || ImGui::IsKeyDown(KeyCode::D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts.GetSec();
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts.GetSec();
		}

		if (input::isKeyPressed(KeyCode::W) || ImGui::IsKeyDown(KeyCode::W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts.GetSec();
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts.GetSec();
		}
		else if (input::isKeyPressed(KeyCode::S) || ImGui::IsKeyDown(KeyCode::S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts.GetSec();
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts.GetSec();
		}

		if (m_Rotation)
		{
			if (input::isKeyPressed(KeyCode::Q) || ImGui::IsKeyDown(KeyCode::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts.GetSec();
			if (input::isKeyPressed(KeyCode::E) || ImGui::IsKeyDown(KeyCode::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts.GetSec();
			
			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetCamRot(m_CameraRotation);
		}

		m_Camera.SetCamPos(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel * 2.7f;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(FR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::ResizeBounds(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e )
	{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		FR_TRACE(m_ZoomLevel);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{

		ResizeBounds((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}