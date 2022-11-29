#pragma once

#include <memory>
#include "buffers.h"

namespace Forge {

	class vertex_array
	{
	public:
		virtual ~vertex_array() = default;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void AddVertexBuffer(const FRef<vertex_buffer>& vb)  = 0;

		virtual void SetIndexBuffer(const FRef<index_buffer>& ib) = 0;

		//Added functionality to retrieve what the vertex array stores.
		virtual const std::vector<FRef<vertex_buffer>>& GetVertexBuffers() const = 0;
		virtual const FRef<index_buffer>& GetIndexBuffers() const = 0;

		static FRef<vertex_array> create();
	};



}