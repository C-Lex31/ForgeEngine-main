#include "frpch.h"
#include "vertex_array.h"
#include "renderer_rd.h"
#include "core/drivers/OpenGL/opengl_vertexArray.h"
namespace Forge {


	FRef<vertex_array> vertex_array::create()
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None: return nullptr;
		case renderer_api::api::OpenGL: return std::make_shared <OpenGLVertexArray>();
		}
		return 0;
	}



}