#pragma once

#include "core/servers/rendering/core_rd/vertex_array.h"

namespace Forge {

	class OpenGLVertexArray:public vertex_array
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() {}
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void AddVertexBuffer(const FRef<vertex_buffer>& vb) override;
		virtual void SetIndexBuffer(const FRef<index_buffer>& ib) override;
		//TODO: Add Index buffer to array
	    virtual const std::vector<FRef<vertex_buffer>>& GetVertexBuffers() const { return m_vertexBuffers; }
	    virtual const FRef<index_buffer>& GetIndexBuffers() const { return m_indexBuffers; }
	private:
		std::vector<FRef<vertex_buffer>> m_vertexBuffers;
		FRef<index_buffer> m_indexBuffers;
		uint32_t m_rendererID;
	};
}