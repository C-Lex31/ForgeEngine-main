#include "frpch.h"
#include "opengl_framebuffer.h"

namespace Forge {

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecs& spec)
		:m_Specification(spec)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);

			//m_DepthAttachment = 0;
		}
		glCreateFramebuffers(1, &m_RendererID);
	//	glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		//glGenTextures(1, &m_ColorAttachment);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.width, m_Specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

	//	glGenTextures(1, &m_DepthAttachment);
		glCreateTextures(GL_TEXTURE_2D,1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height);

	//	glTexImage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		FR_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Incomplete Framebuffer Generated !");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::resize(uint32_t vp_width, uint32_t vp_height) 
	{
		m_Specification.width = vp_width;
		m_Specification.height = vp_height;
		Invalidate();
	}

	void OpenGLFramebuffer::bind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.width, m_Specification.height);
	}

	void OpenGLFramebuffer::unbind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}