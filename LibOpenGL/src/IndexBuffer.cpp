#pragma once

#include <LibOpenGL/Defines.h>
#include <LibOpenGL/IndexBuffer.h>

#include <glad/glad.h>

#include <iostream>

namespace libgl
{
	IndexBuffer::IndexBuffer(unsigned int* indices, std::size_t indexCount)
		: Bindable()
		, m_vi{0}
		, m_indexCount{indexCount}
	{
		GlCall(glGenBuffers(1, &m_vi));
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vi));
		GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW));
	}

	void IndexBuffer::bind() const { GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vi)); }


	void IndexBuffer::unbind() const
	{
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		GlCall(glDeleteBuffers(1, &m_vi));
	};
}