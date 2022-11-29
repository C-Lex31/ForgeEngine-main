#include "frpch.h"
#include "opengl_renderer.h"
#include "glad/glad.h"
namespace Forge {

	void OpenGLRendererAPI::Init()
	{
		FR_CORE_INFO("Initialized Renderer ");
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

    void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glDisable(GL_BLEND);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

    void OpenGLRendererAPI::drawElements(const FRef<vertex_array>& va , uint32_t index_count )
	{
	
		uint32_t count = index_count==0 ? va->GetIndexBuffers()->GetCount() : index_count;
		glDrawElements(GL_TRIANGLES, count , GL_UNSIGNED_INT, nullptr);
	//	glBindTexture(GL_TEXTURE_2D, 0);
	}
	float OpenGLRendererAPI::GetTime()
	{
		return glfwGetTime();
	}


}