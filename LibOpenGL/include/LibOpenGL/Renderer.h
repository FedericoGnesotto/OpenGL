#pragma once

namespace libgl
{

	class VertexArray;
	class IndexBuffer;
	class Shader;

	class Renderer
	{
	public:
		Renderer() = default;
		virtual ~Renderer() = default;

		virtual void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& sh) const;
		virtual void draw(const VertexArray& va, const Shader& sh, int vertexCount) const;
	};
}