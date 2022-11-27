#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/matrix.hpp>

struct GLFWwindow;

namespace libgl
{
	struct Mouse
	{
		double posX = 0.0;
		double posY = 0.0;
		const float sensitivity = 0.1f;
		bool startedPress = false;
	};

	class Camera
	{
	public:
		Camera() = default;
		void handleScroll(double xOffset, double yOffset);

		void handleMouse(double x, double y);

		void handleKey(GLFWwindow* window, float deltaT);

		const glm::mat4& view() const { return m_viewMatrix; }

		const glm::mat4& proj() const { return m_projectionMatrix; }

		Mouse& mouse() { return m_mouse; }

	private:
		float m_fov = 45.0f;    //radians
		glm::mat4 m_viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 m_projectionMatrix = glm::perspective(glm::radians(m_fov), 800.0f / 600.0f, 0.1f, 100.0f);

		double m_yaw = 0.0;
		double m_pitch = 0.0;
		//double roll = 0.0;

		Mouse m_mouse{};    // definitely weird, mouse and camera should belong to the window probably
	};
}