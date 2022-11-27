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


	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	libgl::Shader shader("../../LibOpenGL/res/shaders/Shader.shader");
	shader.use();

	libgl::Texture tex{};
	tex.configure();
	tex.bind();
	shader.setUniform1i("u_Texture", 0);
	tex.loadFrom("../../LibOpenGL/res/textures/container.jpg");

	libgl::FrameBuffer fbo{};
	fbo.attach(tex);

	tex.destroy();    //needs to be called before glfwTerminate or it will end up in an infinite loop

	glfwTerminate();
	return 0;
}