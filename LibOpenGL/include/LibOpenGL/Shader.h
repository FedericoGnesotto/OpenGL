#pragma once

#include <glad/glad.h>

#include <glm/matrix.hpp>

#include <string>
namespace libgl
{

	class Shader
	{
	public:
		Shader(const std::string& shaderPath);

		unsigned int fragment() const { return _fragmentShaderId; }
		unsigned int vertex() const { return _vertexShaderId; }

		void use() const { glUseProgram(_shaderProgram); };

		~Shader() { glDeleteProgram(_shaderProgram); }

		void setUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
		void setUniform1i(const std::string& name, int i);
		void setUniformMat4f(const std::string& name, const glm::mat4 matrix);

	private:
		void loadShader(const std::string& shaderPath);

		void compileShader();

		unsigned int _vertexShaderId;
		unsigned int _fragmentShaderId;
		unsigned int _shaderProgram;
		std::string _fragmentShaderSrc;
		std::string _vertexShaderSrc;
	};
}