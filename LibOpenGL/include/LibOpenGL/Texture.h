#pragma once

#include <LibOpenGL/Bindable.h>

#include <map>
#include <string_view>

namespace libgl
{
	const std::map<GLenum, GLint> DefaultTextureConfig = {{GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT},
														  {GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT},
														  {GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR},
														  {GL_TEXTURE_MAG_FILTER, GL_LINEAR}};

	class Texture
	{
	public:
		Texture();

		void bind(unsigned int slot = 0) const;
		void configure(const std::map<GLenum, GLint>& config = DefaultTextureConfig) const;
		void generate(int width, int height, int channelsCount, void* data, GLenum type = GL_RGB) const;


		unsigned id() const { return m_textureId; }
		int width() const { return m_width; }
		int height() const { return m_height; }

		void loadFrom(std::string_view path);
		void unbind() const;
		void destroy() const;

	private:
		unsigned m_textureId = 0;
		int m_width = 0, m_height = 0, m_channels = 0;
	};
}