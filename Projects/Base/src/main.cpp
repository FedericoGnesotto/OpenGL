// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <LibOpenGL/Camera.h>
#include <LibOpenGL/Defines.h>
#include <LibOpenGL/IndexBuffer.h>
#include <LibOpenGL/Renderer.h>
#include <LibOpenGL/Shader.h>
#include <LibOpenGL/Texture.h>
#include <LibOpenGL/Utils.h>
#include <LibOpenGL/VertexArray.h>
#include <LibOpenGL/VertexBuffer.h>
#include <LibOpenGL/VertexBufferLayout.h>
#include <LibOpenGL/View.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/matrix.hpp>

#include <algorithm>
#include <corecrt_math_defines.h>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

void processInput(libgl::View& view, float deltaT)
{
	if (glfwGetKey(view.window(), GLFW_KEY_ESCAPE) == GLFW_PRESS)    // escape
		glfwSetWindowShouldClose(view.window(), true);
	else
		view.handleKey(deltaT);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);    // opengl 4.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);    // opengl .6
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	libgl::View view{window};

	float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
						0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

						-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
						0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

						-0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
						-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,
						0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
						0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

						-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
						0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

						-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

	// this stuff should also be done in the view probably
	libgl::VertexBuffer vb{vertices, std::size(vertices)};
	//learnGl::IndexBuffer ib{indices, std::size(indices)};


	libgl::Shader shader("../../LibOpenGL/res/shaders/Shader.shader");
	shader.use();


	libgl::VertexArray va{};
	va.bind();
	vb.bind();

	libgl::Texture tex{};
	tex.configure();
	tex.bind();
	shader.setUniform1i("u_Texture", 0);
	tex.loadFrom("../../LibOpenGL/res/textures/container.jpg");

	libgl::VertexBufferLayout layout{};
	layout.push<float>(3, false);
	layout.push<float>(2, false);
	va.add(layout);

	libgl::Renderer renderer{};

	std::vector<glm::vec3> randomDir(10);
	std::generate(randomDir.begin(), randomDir.end(), []() { return glm::vec3(std::rand(), std::rand(), std::rand()); });

	glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(2.0f, 5.0f, -15.0f),
								 glm::vec3(-1.5f, -2.2f, -2.5f),
								 glm::vec3(-3.8f, -2.0f, -12.3f),
								 glm::vec3(2.4f, -0.4f, -3.5f),
								 glm::vec3(-1.7f, 3.0f, -7.5f),
								 glm::vec3(1.3f, -2.0f, -2.5f),
								 glm::vec3(1.5f, 2.0f, -2.5f),
								 glm::vec3(1.5f, 0.2f, -1.5f),
								 glm::vec3(-1.3f, 1.0f, -1.5f)};

	glEnable(GL_DEPTH_TEST);
	double currentFrame = 0.0;
	double lastFrame = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		currentFrame = glfwGetTime();
		float deltaT = float(currentFrame - lastFrame);
		lastFrame = currentFrame;

		processInput(view, deltaT * 10.0f);

		////Call(glClearColor(0.1f, 0.3f, 0.4f, 1.0f));
		GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		for (auto i = 0; i < 10; i++)
		{
			glm::mat4 model{1.0f};
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, float(M_PI_4), randomDir[i]);
			//model = glm::translate(model, glm::vec3(std::rand(), std::rand(), std::rand()));

			glm::mat4 mvpMat = view.projView() * model;
			shader.setUniformMat4f("u_MVP", mvpMat);
			renderer.draw(va, shader);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vb.unbind();
	//ib.unbind();
	va.unbind();
	tex.destroy();    //needs to be called before glfwTerminate or it will end up in an infinite loop

	glfwTerminate();

	return 0;
}
