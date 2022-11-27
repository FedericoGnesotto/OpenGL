#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <LibOpenGL/Camera.h>
#include <LibOpenGL/Utils.h>

namespace libgl
{
	void Camera::handleScroll(double xOffset, double yOffset)
	{
		m_fov -= (float)yOffset;
		if (m_fov < 1.0f)
			m_fov = 1.0f;
		else if (m_fov > 45.0f)
			m_fov = 45.0f;

		m_projectionMatrix = glm::perspective(glm::radians(m_fov), 800.0f / 600.0f, 0.1f, 100.0f);
	}

	void Camera::handleMouse(double x, double y)
	{
		auto deltaX = x - m_mouse.posX;
		auto deltaY = y - m_mouse.posY;

		m_mouse.posX = x;
		m_mouse.posY = y;

		deltaX *= m_mouse.sensitivity;
		deltaY *= m_mouse.sensitivity;

		m_yaw += deltaX;
		m_pitch += deltaY;

		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		else if (m_pitch < -89.0f)
			m_pitch = -89.0f;

		glm::vec3 cameraDir{};
		cameraDir.x = std::cosf(glm::radians((float)m_pitch)) * std::cosf(glm::radians((float)m_yaw));
		cameraDir.y = std::sinf(glm::radians((float)m_pitch));
		cameraDir.z = std::cosf(glm::radians((float)m_pitch)) * std::sinf(glm::radians((float)m_yaw));
		cameraDir = glm::normalize(cameraDir);

		m_viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 0.f, -1.f) + cameraDir, glm::vec3(0.f, 1.f, 0.f));

		utils::printMat(m_viewMatrix);
	}

	void Camera::handleKey(GLFWwindow* window, float deltaT)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)    // right
			m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(-1.0f, 0.0f, 0.0f) * deltaT);
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)    // left
			m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(1.0f, 0.0f, 0.0f) * deltaT);
		else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)    // up
			m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, -1.0f, 0.0f) * deltaT);
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)    // down
			m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, 1.0f, 0.0f) * deltaT);
	}
}