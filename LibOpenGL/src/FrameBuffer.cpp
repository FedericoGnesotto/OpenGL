
#include <LibOpenGL/Defines.h>
#include <LibOpenGL/FrameBuffer.h>

#include <glad/glad.h>

namespace libgl
{

	FrameBuffer::FrameBuffer() { GlCall(glGenFramebuffers(1, &m_fbo)); }

	void FrameBuffer::bind() const
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG("Framebuffer.Framebuffer is not complete!");
			ASSERT(false);
			return;
		}

		GlCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
	}

	void FrameBuffer::attach(const Texture& tex, GLenum type) const { glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, tex.id(), 0); }

	void FrameBuffer::unbind() const { GlCall(glDeleteFramebuffers(1, &m_fbo)); }
}
