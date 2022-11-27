#include <LibOpenGL/Defines.h>
#include <LibOpenGL/Utils.h>
#include <LibOpenGL/View.h>

#include <GLFW/glfw3.h>


namespace libgl
{
	namespace
	{
		void framebuffer_size_callback(GLFWwindow* window, int width, int height) { GlCall(glViewport(0, 0, width, height)); }
	}

	// int here is fine because GL will throw an error if width/height are negative
	View::View(GLFWwindow* window, int width, int height)
		: m_window{window}
		, m_cam{}

	{
		if (!window)
		{
			LOG("Failed to create GLFW window");
			glfwTerminate();
		}


		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG("Failed to initialize GLAD");
		}

		libgl::utils::printGLVersion();

		glViewport(0, 0, width, height);

		// register callbacks
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


		glfwSetWindowUserPointer(window, this);

		glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y) {
			auto self = reinterpret_cast<View*>(glfwGetWindowUserPointer(window));
			ASSERT(self);
			self->m_cam.handleScroll(x, y);
		});

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			auto self = reinterpret_cast<View*>(glfwGetWindowUserPointer(window));
			ASSERT(self);
			if (self->m_cam.mouse().startedPress)
			{
				LOG("Continuing");
				self->m_cam.handleMouse(xpos, ypos);
				return;
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			auto self = reinterpret_cast<View*>(glfwGetWindowUserPointer(window));
			ASSERT(self);
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			{
				auto& started = self->m_cam.mouse().startedPress;
				if (!started)
				{
					LOG("Starting");
					started = true;
					double posX = 0.0, posY = 0.0;
					glfwGetCursorPos(window, &posX, &posY);
					self->m_cam.mouse().posX = posX;
					self->m_cam.mouse().posY = posY;
					return;
				}
			}
			else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
			{
				auto& started = self->m_cam.mouse().startedPress;
				if (started)
				{
					LOG("Release");
					started = false;
					return;
				}
			}
		});
	}

	void View::handleKey(float deltaT) { m_cam.handleKey(m_window, deltaT); }

	glm::mat4 View::projView() const { return m_cam.proj() * m_cam.view(); }

}