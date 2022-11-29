#pragma once
#include"core/servers/rendering/core_rd/graphics_context.h"
namespace Forge {

	class opengl_context :public graphics_context
	{
	public:
		opengl_context(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void swap_buffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}
