
#include <LibOpenGL/IndexBuffer.h>
#include <LibOpenGL/Renderer.h>
#include <LibOpenGL/Shader.h>
#include <LibOpenGL/VertexArray.h>

namespace libgl
{
	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& sh)
	{
		ib.bind();
		va.bind();
		sh.use();
		GlCall(glDrawElements(GL_TRIANGLES, (int)ib.indexCount(), GL_UNSIGNED_INT, 0));
	}

	void Renderer::draw(const VertexArray& va, const Shader& sh)
	{
		va.bind();
		sh.use();
		GlCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	}
}