#pragma once

#include "Hazel.h"

class OrthographicFollowCameraController
{
public:
	OrthographicFollowCameraController(float aspectRatio, bool rotation = false);

	void OnUpdate(Hazel::Timestep ts);
	void OnEvent(Hazel::Event& e);

	Hazel::OrthographicCamera& GetCamera() { return m_Camera; }
	const Hazel::OrthographicCamera& GetCamera() const { return m_Camera; }

	float GetZoomLevel() const { return m_ZoomLevel; }
	void SetZoomLevel(float level) { m_ZoomLevel = level; }
private:
	bool OnMouseScrolled(Hazel::MouseScrolledEvent& e);
	bool OnWindowResized(Hazel::WindowResizeEvent& e);
private:
	float m_AspectRatio;
	float m_ZoomLevel = 1.0f;
	Hazel::OrthographicCamera m_Camera;

	bool m_Rotation;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
	float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
};
