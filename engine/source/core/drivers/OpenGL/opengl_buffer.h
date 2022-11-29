#pragma once
#include"core/servers/rendering/core_rd/buffers.h"

namespace Forge {
	class OpenGLVertexBuffer:public vertex_buffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer( uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const buffer_layout& GetLayout()const override { return m_layout; }
		virtual void SetLayout(const buffer_layout& layout) override { m_layout = layout; }
		virtual void SetData(const void* data, uint32_t size) override;
	private:
	uint32_t m_rendererID;
	buffer_layout m_layout;
	};

	class OpenGLIndexBuffer : public index_buffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const ;
		virtual void unbind() const ;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_rendererID;
		uint32_t m_Count;
	};
	
	




}