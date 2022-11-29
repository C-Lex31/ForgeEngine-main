#include "frpch.h"
#include"framebuffer.h"
#include "renderer_rd.h"
#include "core/drivers/OpenGL/opengl_framebuffer.h"
namespace Forge {
	FRef<Framebuffer> Framebuffer::create(const FramebufferSpecs& spec)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None: return nullptr;
		case renderer_api::api::OpenGL: return std::make_shared <OpenGLFramebuffer>(spec);
		}
		return 0;
	}
}