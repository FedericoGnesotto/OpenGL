#include <glad/glad.h>

#include <LibOpenGL/Defines.h>
#include <LibOpenGL/Texture.h>
#include <stb/stb_image.h>

namespace libgl
{
	Texture::Texture() { GlCall(glGenTextures(1, &m_textureId)); }

	void Texture::bind(unsigned int slot /*=0*/) const
	{
		GlCall(glActiveTexture(GL_TEXTURE0 + slot));
		GlCall(glBindTexture(GL_TEXTURE_2D, m_textureId));
	}

	void Texture::configure(const std::map<GLenum, GLint>& config) const
	{
		for (const auto& c : config)
			glTexParameteri(GL_TEXTURE_2D, c.first, c.second);
	}

	void Texture::generate(int width, int height, int channelsCount, void* data, GLenum type, bool mipmap) const
	{
		GlCall(glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data == nullptr ? 0 : data));
		if (mipmap)
			GlCall(glGenerateMipmap(GL_TEXTURE_2D));
	}


	void Texture::loadFrom(std::string_view path)
	{
		unsigned char* data = stbi_load(path.data(), &m_width, &m_height, &m_channels, 0);
		if (!data)
		{
			ASSERT(false);
			std::cout << "Failed to load texture" << std::endl;
			return;
		}

		generate(m_width, m_height, m_channels, data);
		stbi_image_free(data);
	}

	void Texture::unbind() const { GlCall(glBindTexture(GL_TEXTURE_2D, 0)); }

	void Texture::destroy() const { GlCall(glDeleteTextures(1, &m_textureId)); }
}
