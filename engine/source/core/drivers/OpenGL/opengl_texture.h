#pragma once
#include "glad/glad.h"
#include "core/servers/rendering/core_rd/texture.h"
namespace Forge {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const FString& path , const uint32_t slot);
		OpenGLTexture2D(uint32_t width, uint32_t height, void* data);
		virtual ~OpenGLTexture2D();
		virtual uint32_t GetTexWidth() const override { return m_TexWidth; }
		virtual uint32_t GetTexHeight() const override { return m_TexHeight; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }
		virtual void bind(uint32_t slot) const override;
		virtual bool operator==(const Texture& other) const override { return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID; }
	private:
		FString m_Path;
		uint32_t m_TexWidth;
		uint32_t m_TexHeight;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};


}