#pragma once

#include <LibOpenGL/Bindable.h>
#include <LibOpenGL/Texture.h>

#include <vector>

namespace libgl
{
	class FrameBuffer : public Bindable
	{
	public:
		FrameBuffer();

		void bind() const override;

		void attach(const Texture& tex, GLenum type = GL_COLOR_ATTACHMENT0);

		void unbind() const override;

		void setDrawBuffers();

	private:
		unsigned int m_fbo = 0;
		std::vector<GLenum> m_buffers;
	};
}