#pragma once

#include <LibOpenGL/Bindable.h>
#include <LibOpenGL/Texture.h>

namespace libgl
{
	class FrameBuffer : public Bindable
	{
	public:
		FrameBuffer();

		void bind() const override;

		void attach(const Texture& tex, GLenum type = GL_COLOR_ATTACHMENT0) const;

		void unbind() const override;

	private:
		unsigned int m_fbo;
	};
}