#pragma once
//API for the renderer
#include "glm/glm.hpp"
#include "vertex_array.h"
namespace Forge {

	class renderer_api
	{
	public:
		enum class api
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void clear() = 0;
		virtual void drawElements(const FRef<vertex_array>& va , uint32_t index_count = 0) = 0;
		virtual float GetTime() = 0;
		inline static api getAPI() { return s_api; };
	private:
		static api s_api;
	};

}
