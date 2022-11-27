
#include <LibOpenGL/Defines.h>
#include <LibOpenGL/VertexBuffer.h>

#include <glm/geometric.hpp>

namespace libgl
{
	VertexBuffer::VertexBuffer(float* vertices, std::size_t vertexCount)
		: Bindable()
	{
		GlCall(glGenBuffers(1, &m_vb));
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb));
		GlCall(glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW));
	}

	void VertexBuffer::bind() const { GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vb)); }

	void VertexBuffer::unbind() const
	{
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GlCall(glDeleteBuffers(1, &m_vb));
	}
}
