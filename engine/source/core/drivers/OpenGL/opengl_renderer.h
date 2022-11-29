#pragma once

#include "core/servers/rendering/core_rd/renderer_api.h"

namespace Forge {

	class OpenGLRendererAPI:public renderer_api
	{
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	    virtual void drawElements(const FRef<vertex_array>& va , uint32_t index_count =0) override;
		virtual float GetTime();
	};

}
