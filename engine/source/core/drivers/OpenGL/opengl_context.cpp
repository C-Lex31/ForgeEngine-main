#include "frpch.h"
#include "opengl_context.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
namespace Forge {

	opengl_context::opengl_context(GLFWwindow* windowHandle)
		:m_windowHandle(windowHandle) {}

	void opengl_context::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (glGetString(GL_VENDOR) == NULL)
			FR_CORE_FATAL("Vendor not found ! Please restart the application or your system.");

		FR_CORE_WARN("Vendor  :{0}", glGetString(GL_VENDOR));

		FR_CORE_WARN("Renderer:{0}", glGetString(GL_RENDERER));
		FR_CORE_WARN("Version :{0}", glGetString(GL_VERSION));

		
	}
	void opengl_context::swap_buffers()
	{
		
		glfwSwapBuffers(m_windowHandle);
	}
}