#include "frpch.h"
#include <fstream>
#include <cerrno>
#include <iostream>
#include "shader.h"
#include "renderer_rd.h"
#include "core/drivers/OpenGL/opengl_shader.h"
namespace Forge {

	
	FRef<shader> shader::create(const FString& filepath)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None: return nullptr;
		case renderer_api::api::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}
		return 0;
	}
	/*FRef<shader> shader::create(const FString& vertexFile, const FString& fragFile)
	{
		
		switch (renderer::get_api())
		{
		case renderer_api::api::None: return nullptr;
		case renderer_api::api::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc,fragSrc);
		}
		return 0;
	}*/

	



}