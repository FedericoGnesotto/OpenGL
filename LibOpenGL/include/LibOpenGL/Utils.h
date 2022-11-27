#pragma once

#include <glad/glad.h>

#include <glm/matrix.hpp>

#include <iostream>

namespace libgl::utils
{

	void printMat(const glm::mat4& matr);

	void glClearError();

	bool glCheckError(int line, const char* file);

	void printGLVersion();

	void checkShaderCompiled(unsigned int shader);

	void checkShaderLinked(unsigned shaderProgram);
}