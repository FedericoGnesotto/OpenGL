#include <LibOpenGL/Defines.h>
#include <LibOpenGL/Utils.h>

#include <iomanip>

void libgl::utils::glClearError()
{
	while (glGetError() != GL_NO_ERROR)
	{
		GlCall(glClearError());
	}
}

bool libgl::utils::glCheckError(int line, const char* file)
{
	while (auto err = glGetError())
	{
		std::cout << "***************"
				  << "\n";
		std::cout << "GLError: " << err << "\n" << file << ": " << line << std::endl;
		return false;
	}
	return true;
}

void libgl::utils::printGLVersion() { std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; }

void libgl::utils::checkShaderCompiled(unsigned int shader)
{
	int success;
	char infoLog[512];
	GlCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GlCall(glGetShaderInfoLog(shader, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void libgl::utils::checkShaderLinked(unsigned shaderProgram)
{
	int success{};
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::FRAGMENT::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void libgl::utils::printMat(const glm::mat4& matr)
{
	for (int i = 0; i < 4; ++i)
	{
		std::cout << "|";
		for (int j = 0; j < 4; ++j)
			std::cout << std::setw(6) << std::setprecision(2) << matr[j][i] << " ";

		std::cout << "|\n";
	}
}
