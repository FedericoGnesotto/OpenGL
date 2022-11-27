#pragma once

#include <LibOpenGL/Camera.h>

struct GLFWwindow;

namespace libgl
{
	class View
	{
	public:
		explicit View(GLFWwindow* window, int width = 800, int height = 600);

		GLFWwindow* window() const { return m_window; }
		void handleKey(float deltaT);
		glm::mat4 projView() const;

	private:
		GLFWwindow* m_window;
		Camera m_cam;
	};
}