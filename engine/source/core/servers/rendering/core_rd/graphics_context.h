#pragma once

namespace Forge {

	class graphics_context
	
	{
	public:
		virtual void Init() = 0;
		virtual void swap_buffers() = 0;

	};

}