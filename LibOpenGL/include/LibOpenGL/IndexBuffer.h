#pragma once

#include <LibOpenGL/Bindable.h>

#include <glad/glad.h>

#include <iostream>

namespace libgl
{
	class IndexBuffer : public Bindable
	{
	public:
		explicit IndexBuffer(unsigned int*, std::size_t indicesCount);

		void bind() const override;

		void unbind() const override;

		inline std::size_t indexCount() const { return m_indexCount; }

	private:
		unsigned m_vi = 0;
		std::size_t m_indexCount = 0;
	};
}