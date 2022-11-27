#pragma once

#include <LibOpenGL/Bindable.h>
#include <LibOpenGL/VertexBufferLayout.h>

#include <vector>

namespace libgl
{
	class VertexArray : public Bindable
	{
	public:
		VertexArray();

		void bind() const override;

		void add(const VertexBufferLayout& layout) const;

		void unbind() const override;

	private:
		unsigned int m_va;
	};
}