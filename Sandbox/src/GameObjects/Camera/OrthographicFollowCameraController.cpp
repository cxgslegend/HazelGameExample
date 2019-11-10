#include "OrthographicFollowCameraController.h"

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

OrthographicFollowCameraController::OrthographicFollowCameraController(float aspectRatio, bool rotation)
	: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
{
}

void OrthographicFollowCameraController::OnUpdate(Hazel::Timestep ts)
{
	if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
	{
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}
	else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
	{
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}

	if (Hazel::Input::IsKeyPressed(HZ_KEY_W))
	{
		m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}
	else if (Hazel::Input::IsKeyPressed(HZ_KEY_S))
	{
		m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}

	if (m_Rotation)
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_Camera.SetRotation(m_CameraRotation);
	}

	m_Camera.SetPosition(m_CameraPosition);

	m_CameraTranslationSpeed = m_ZoomLevel;
}

void OrthographicFollowCameraController::OnEvent(Hazel::Event& e)
{
	Hazel::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Hazel::MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicFollowCameraController::OnMouseScrolled));
	dispatcher.Dispatch<Hazel::WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicFollowCameraController::OnWindowResized));
}

bool OrthographicFollowCameraController::OnMouseScrolled(Hazel::MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool OrthographicFollowCameraController::OnWindowResized(Hazel::WindowResizeEvent& e)
{
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}
