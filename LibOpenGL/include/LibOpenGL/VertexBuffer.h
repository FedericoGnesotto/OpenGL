#pragma once

#include <LibOpenGL/Bindable.h>

#include <glad/glad.h>

#include <iostream>

namespace libgl
{
	class VertexBuffer : public Bindable
	{
	public:
		explicit VertexBuffer(float* vertices, std::size_t vertexCount);

		void bind() const override;


		void unbind() const override;

	private:
		unsigned m_vb = 0;
	};
}