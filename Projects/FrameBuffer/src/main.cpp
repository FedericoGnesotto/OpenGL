// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <LibOpenGL/Camera.h>
#include <LibOpenGL/Defines.h>
#include <LibOpenGL/FrameBuffer.h>
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

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);    // opengl 4.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);    // opengl .6
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "FrameBuffer", NULL, NULL);

	libgl::View view{window};

	// clang-format off
	float quadVertices[] = {-1.f, -1.f, 0.f, 0.0f, 0.0f,
							-1.f, 1.f, 0.f, 0.0f, 1.0f,
							1.f, 1.f, 0.f, 1.0f, 1.0f,
							1.f, 1.f, 0.f, 1.0f, 1.0f,
							1.f, -1.f, 0.f, 1.0f, 0.0f,
							-1.f, -1.f, 0.f, 0.0f, 0.0f};
	// clang-format on

	libgl::VertexBuffer quadVBO{quadVertices, std::size(quadVertices)};
	quadVBO.bind();
	libgl::VertexBufferLayout layout{};
	layout.push<float>(3, false);
	layout.push<float>(2, false);
	libgl::VertexArray quadVAO{};
	quadVAO.bind();
	quadVAO.add(layout);

	libgl::Shader inversionShader("../../LibOpenGL/res/shaders/InversionShader.shader");
	inversionShader.use();


	libgl::Texture texIn{};
	texIn.configure({{GL_TEXTURE_MIN_FILTER, GL_LINEAR}, {GL_TEXTURE_MAG_FILTER, GL_LINEAR}});
	texIn.bind(0);
	inversionShader.setUniform1i("u_InputTexture", 0);
	texIn.loadFrom("../../LibOpenGL/res/textures/container.jpg");
	int width = texIn.width();
	int height = texIn.height();
	glViewport(0, 0, width, height);


	libgl::Texture texOut{};
	texOut.configure({{GL_TEXTURE_MIN_FILTER, GL_LINEAR}, {GL_TEXTURE_MAG_FILTER, GL_LINEAR}});
	texOut.bind(1);
	texOut.generate(width, height, texIn.channels(), nullptr, GL_RGB, false);

	libgl::FrameBuffer fbo{};
	fbo.bind();
	fbo.attach(texOut, GL_COLOR_ATTACHMENT0);
	//fbo.setDrawBuffers();

	libgl::Renderer renderer{};
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // we're not using the stencil buffer now
	renderer.draw(quadVAO, inversionShader, (int)std::size(quadVertices));
	fbo.unbind();
	texIn.unbind();

	libgl::Shader screenShader("../../LibOpenGL/res/shaders/Shader.shader");
	screenShader.use();
	while (!glfwWindowShouldClose(window))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);    // disable depth test so screen-space quad isn't discarded due to depth test.
		// clear all relevant buffers
		glClear(GL_COLOR_BUFFER_BIT);
		texOut.bind(0);
		screenShader.setUniform1i("u_Texture", 0);
		screenShader.use();
		glm::mat4 mvpMat = glm::identity<glm::mat4>();
		mvpMat = glm::translate(mvpMat, glm::vec3(0, 0, -1));

		screenShader.setUniformMat4f("u_MVP", mvpMat);
		renderer.draw(quadVAO, screenShader, (int)quadVBO.vertexCount());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	texIn.destroy();     //needs to be called before glfwTerminate or it will end up in an infinite loop
	texOut.destroy();    //needs to be called before glfwTerminate or it will end up in an infinite loop

	glfwTerminate();
	return 0;
}