#pragma once


#include <LibOpenGL/Defines.h>

#include <glad/glad.h>

#include <vector>

namespace libgl
{
	class VertexBufferLayout
	{
		struct Element
		{
			Element(unsigned int type, unsigned int count, unsigned int normalized)
				: m_type{type}
				, m_count{count}
				, m_normalized{normalized}
			{
			}
			unsigned int m_type;
			unsigned int m_count;
			unsigned int m_normalized;
			inline static std::uintptr_t getTypeSize(unsigned int type)
			{
				switch (type)
				{
				case GL_FLOAT:
					return 4;
				case GL_UNSIGNED_INT:
					return 4;
				case GL_UNSIGNED_BYTE:
					return 1;
				default:
					break;
				}
				ASSERT(false);
				return 0;
			}
		};

	public:
		VertexBufferLayout() {}

		inline std::size_t size() const { return m_elements.size(); }

		inline const Element& el(unsigned int i) const { return m_elements[i]; }

		template <typename T>
		void push(unsigned int count, bool normalized)
		{
		}

		template <>
		void push<float>(unsigned int count, bool normalized)
		{
			m_elements.emplace_back(GL_FLOAT, count, normalized ? 1u : 0u);
			m_stride += count * (unsigned int)Element::getTypeSize(GL_FLOAT);
		}


		template <>
		void push<unsigned int>(unsigned int count, bool normalized)
		{
			m_elements.emplace_back(GL_UNSIGNED_INT, count, normalized ? 1u : 0u);
			m_stride += count * (unsigned int)Element::getTypeSize(GL_UNSIGNED_INT);
		}


		template <>
		void push<unsigned char>(unsigned int count, bool normalized)
		{
			m_elements.emplace_back(GL_UNSIGNED_BYTE, count, normalized ? 1u : 0u);
			m_stride += count * (unsigned int)Element::getTypeSize(GL_UNSIGNED_BYTE);
		}

		inline unsigned stride() const { return m_stride; }

	private:
		std::vector<Element> m_elements;
		unsigned m_stride = 0;
	};

}