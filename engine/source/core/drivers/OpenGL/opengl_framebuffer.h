#pragma once
#include "core/servers/rendering/core_rd/framebuffer.h"
#include "glad/glad.h"
namespace Forge {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecs& spec);
		virtual ~OpenGLFramebuffer();
		void Invalidate();
		virtual const FramebufferSpecs& GetFSpecs() const override { return m_Specification; }
		virtual const uint32_t GetColorAttachmentID() const override { return m_ColorAttachment; }
		virtual void resize(uint32_t vp_width, uint32_t vp_height)  override;
		virtual void bind()  override;
		virtual void unbind() override;
	private:
		FramebufferSpecs m_Specification;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment=0;
		uint32_t m_RendererID=0;
	};
}
