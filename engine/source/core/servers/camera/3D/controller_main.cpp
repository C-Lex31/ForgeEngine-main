#include "frpch.h"
#include "controller_main.h"

#include "core/input/input.h"
#include "imgui.h"
#include "core/input/keycodes.h"
#include "core/input/mouse_button_codes.h"
namespace Forge {

	CameraController::CameraController(float AspectRatio , glm::vec3 position)//float width , float height, glm::vec3 position)
		:m_AspectRatio(AspectRatio) , m_Camera(-m_AspectRatio * fov , m_AspectRatio * fov, position ) 
	{

	//	Camera::width = width;
	//	Camera::height = height;
		
		CameraController::Position = position;
		//m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // CAUTION DO NOT CHANGE ORDER 

	}

	void CameraController::OnUpdate(Timestep ts)
	{
		if (input::isKeyPressed(KeyCode::LeftShift))
			CamTranslationSpeed = 3.7f;
		else
			CamTranslationSpeed = 1.5f;
		if (input::isKeyPressed(KeyCode::W))        
			CameraController::Position += CamTranslationSpeed * CameraController::m_Orientation * ts.GetSec();

		if (input::isKeyPressed(KeyCode::S))
			CameraController::Position += CamTranslationSpeed * (-CameraController::m_Orientation) * ts.GetSec();
		if (input::isKeyPressed(KeyCode::A))
			CameraController::Position += CamTranslationSpeed * -glm::normalize(glm::cross((CameraController::m_Orientation), CameraController::up)) * ts.GetSec();
		if (input::isKeyPressed(KeyCode::D))
			CameraController::Position += CamTranslationSpeed * glm::normalize(glm::cross((CameraController::m_Orientation), CameraController::up)) * ts.GetSec();
		if (input::isKeyPressed(KeyCode::E))
			CameraController::Position += CamTranslationSpeed * CameraController::up * ts.GetSec();
		if (input::isKeyPressed(KeyCode::Q))
			CameraController::Position += CamTranslationSpeed * -CameraController::up * ts.GetSec();

		if (input::isMouseButtonPressed(Mouse::Button1))
		{
			input::HideCursor();
			float xPos = input::GetMouseX();
			float yPos = input::GetMouseY();
			if (CameraController::firstMouse)
			{
				lastX = xPos;
				lastY = yPos;
				CameraController::firstMouse = false;
			}


			float xoffset = xPos - lastX;
			float yoffset = lastY - yPos;
			lastX = xPos;
			lastY = yPos;

			float sensitivity = 4.0f;
			xoffset *= sensitivity * ts.GetSec();
			yoffset *= sensitivity * ts.GetSec();

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			CameraController::m_Orientation = glm::normalize(direction);
		}

		else { CameraController::firstMouse = true; input::ShowCursor(); }
		
		m_Camera.SetCamPosition(Position );
		m_Camera.SetCamOrientation(m_Orientation);
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(FR_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FR_BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	void CameraController::ResizeBounds(float width, float height)
	{	
		m_AspectRatio = width / height;
       
		m_Camera.SetProjection(fov, m_AspectRatio);
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		/*m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);*/
		fov -= e.GetYOffset() * 1.5f;
		
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 45.0f)
			fov = 45.0f;
		//FR_TRACE(fov);
		m_Camera.SetProjection(fov , m_AspectRatio);
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		ResizeBounds((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}


}