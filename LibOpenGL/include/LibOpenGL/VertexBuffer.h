#pragma once

#include <glad/glad.h>

#include <LibOpenGL/Bindable.h>

#include <iostream>

namespace libgl
{
	class VertexBuffer : public Bindable
	{
	public:
		explicit VertexBuffer(float* vertices, std::size_t vertexCount);

		void bind() const override;

		std::size_t vertexCount() const { return m_vertexCount; }

		void unbind() const override;

	private:
		unsigned m_vb = 0;
		std::size_t m_vertexCount = 0;
	};
}