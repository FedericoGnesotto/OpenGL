
#include <LibOpenGL/Defines.h>
#include <LibOpenGL/Utils.h>
#include <LibOpenGL/VertexArray.h>

#include <glad/glad.h>

namespace libgl
{
	VertexArray::VertexArray()
		: m_va{0}
	{
		GlCall(glGenVertexArrays(1, &m_va));
	}

	void VertexArray::bind() const { GlCall(glBindVertexArray(m_va)); }

	void VertexArray::add(const VertexBufferLayout& layout) const
	{
		std::uintptr_t offset = 0;
		for (auto i = 0; i < layout.size(); ++i)
		{
			const auto& el = layout.el(i);
			glVertexAttribPointer(i, el.m_count, el.m_type, el.m_normalized, layout.stride(), reinterpret_cast<void*>(offset));
			glEnableVertexAttribArray(i);

			offset += el.m_count * el.getTypeSize(el.m_type);
		}
	}

	void libgl::VertexArray::unbind() const { GlCall(glDeleteBuffers(1, &m_va)); }
}
