#include <LibOpenGL/Defines.h>
#include <LibOpenGL/Shader.h>

#include <fstream>
#include <sstream>
#include <string>

namespace libgl
{
	Shader::Shader(const std::string& shaderPath)
	{
		loadShader(shaderPath);
		compileShader();
		GlCall(_shaderProgram = glCreateProgram());
		GlCall(glAttachShader(_shaderProgram, _vertexShaderId));
		GlCall(glAttachShader(_shaderProgram, _fragmentShaderId));
		GlCall(glLinkProgram(_shaderProgram));
		utils::checkShaderLinked(_shaderProgram);
	}

	void Shader::setUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
	{
		glUniform4f(glGetUniformLocation(_shaderProgram, name.c_str()), f1, f2, f3, f4);
	}

	void Shader::setUniform1i(const std::string& name, int i) { GlCall(glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), i)); }

	void Shader::setUniformMat4f(const std::string& name, const glm::mat4 matrix)
	{
		GlCall(glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, &matrix[0][0]));
	}

	void Shader::loadShader(const std::string& shaderPath)
	{
		std::ifstream fs(shaderPath.data());
		ASSERT(fs.is_open());

		std::string s{};
		std::stringstream shaders[2];
		int type = 0;
		while (getline(fs, s))
		{
			if (s.find("#shader") != std::string::npos)
			{
				if (s.find("fragment") != std::string::npos)
					type = 1;
				else if (s.find("vertex") != std::string::npos)
					type = 0;
			}
			else
			{
				shaders[type] << s << "\n";
			}
		}

		_vertexShaderSrc = shaders[0].str();
		_fragmentShaderSrc = shaders[1].str();
	}

	void Shader::compileShader()
	{
		auto fragmentSrc(_fragmentShaderSrc.c_str());
		auto vertexSrc(_vertexShaderSrc.c_str());

		GlCall(_vertexShaderId = glCreateShader(GL_VERTEX_SHADER));
		GlCall(glShaderSource(_vertexShaderId, 1, &(vertexSrc), NULL));
		GlCall(glCompileShader(_vertexShaderId));
		libgl::utils::checkShaderCompiled(_vertexShaderId);

		GlCall(_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER));
		GlCall(glShaderSource(_fragmentShaderId, 1, &(fragmentSrc), NULL));
		GlCall(glCompileShader(_fragmentShaderId));

		libgl::utils::checkShaderCompiled(_fragmentShaderId);
	}
}