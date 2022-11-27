
#include <glad/glad.h>

#include <LibOpenGL/Defines.h>
#include <LibOpenGL/FrameBuffer.h>

namespace libgl
{

	FrameBuffer::FrameBuffer()
		: m_buffers{}
	{
		GlCall(glGenFramebuffers(1, &m_fbo));
	}

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

	// needs to be extended for multiple attachments of different kind
	void FrameBuffer::attach(const Texture& tex, GLenum type)
	{
		GlCall(glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, tex.id(), 0));
		m_buffers.push_back(type);

		if (const auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER); status != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG("Framebuffer.Framebuffer is not complete!");
			ASSERT(false);
			return;
		}
	}

	void FrameBuffer::unbind() const { GlCall(glDeleteFramebuffers(1, &m_fbo)); }

	// needs to be extended to deal with multiple attachments of different kind
	void FrameBuffer::setDrawBuffers() { glDrawBuffers(1, m_buffers.empty() ? nullptr : &m_buffers[0]); }

}
