#include "frpch.h"
#include "texture.h"
#include "core/servers/rendering/core_rd/renderer_rd.h"
#include "core/drivers/OpenGL/opengl_texture.h"
namespace Forge {

	FRef<Texture2D> Texture2D::create(const FString& path, const uint32_t slot)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None: return nullptr;
		case renderer_api::api::OpenGL: return std::make_shared<OpenGLTexture2D>(path ,slot );
		}
		return 0;
	}
	FRef<Texture2D> Texture2D::create(uint32_t width, uint32_t height, void* data)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None:    FR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case renderer_api::api::OpenGL:  return std::make_shared<OpenGLTexture2D>(width, height,data);
		}

		FR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}