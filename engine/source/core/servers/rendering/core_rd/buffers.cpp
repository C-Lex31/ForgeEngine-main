#include "frpch.h"
#include "buffers.h"
#include "renderer_rd.h"
#include "core/drivers/OpenGL/opengl_buffer.h"
namespace Forge {

	FRef <vertex_buffer> vertex_buffer::create(float* vertices, uint32_t size)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api:: None  : return nullptr;
		case renderer_api::api:: OpenGL: return FCreateRef<OpenGLVertexBuffer>(vertices,size);
		}
		return 0;
	}
	FRef<vertex_buffer> vertex_buffer::create(uint32_t size)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None: return nullptr;
		case renderer_api::api::OpenGL: return FCreateRef<OpenGLVertexBuffer>( size);
		}
		return 0;
	
	}
	FRef<index_buffer> index_buffer::create(uint32_t* indices, uint32_t size)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None  :     return nullptr;
		case renderer_api::api::OpenGL:     return FCreateRef<OpenGLIndexBuffer>(indices, size);
		}

		return nullptr;
		return 0;
	}


}