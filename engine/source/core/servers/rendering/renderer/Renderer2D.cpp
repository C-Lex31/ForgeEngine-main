#include "frpch.h"
#include "Renderer2D.h"
#include "core/servers/rendering/core_rd/vertex_array.h"
#include "core/servers/rendering/core_rd/shader.h"
#include "glm/gtc/matrix_transform.hpp"
namespace Forge {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;

		float TextureIndex;
		float TilingFactor;

		// Editor-only
	//	int EntityID;
	};
	struct Renderer2DData
	{
		FRef<vertex_array> QuadVA;
		FRef<vertex_buffer> QuadVB;
		FRef<shader> QuadShader;
		FRef<Texture2D> WhiteTexture;
		static const uint32_t MaxTextureSlots = 32;

	    static const uint32_t MaxQuads = 10000;
	    static const uint32_t MaxVertices = MaxQuads * 4; 
	    static const uint32_t MaxIndices = MaxQuads * 6; // 6 indices per quad 

	

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<FRef<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;

		glm::vec4 QuadVertexPositions[4];
	};
	static Renderer2DData rdc;

	void Renderer2D::Init()
	{
		rdc.QuadVA = vertex_array::create();

		rdc.QuadVB= vertex_buffer::create(rdc.MaxVertices * sizeof(QuadVertex));
		buffer_layout SQ_layout = {
			{"a_Position" ,ShaderDataType::FRfloat3},
			{"a_Color"    ,ShaderDataType::FRfloat4},
			{"a_TexCoord" ,ShaderDataType::FRfloat2},
			{"a_TextureIndex",ShaderDataType::FRfloat},
			{"a_TilingFactor",ShaderDataType::FRfloat}
			
		};
		rdc.QuadVB->SetLayout(SQ_layout);
		rdc.QuadVA->AddVertexBuffer(rdc.QuadVB);
		rdc.QuadVertexBufferBase = new QuadVertex[rdc.MaxVertices];

		uint32_t* QuadIndices = new uint32_t[rdc.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < rdc.MaxIndices; i += 6)
		{
			QuadIndices[i + 0] = offset + 0;
			QuadIndices[i + 1] = offset + 1;
			QuadIndices[i + 2] = offset + 2;

			QuadIndices[i + 3] = offset + 2;
			QuadIndices[i + 4] = offset + 3;
			QuadIndices[i + 5] = offset + 0;
			offset += 4;
		}
		FRef<index_buffer>QuadIB = index_buffer::create(QuadIndices, rdc.MaxIndices);
		rdc.QuadVA->SetIndexBuffer(QuadIB);
		delete[] QuadIndices;

		

		
		uint32_t WhiteTexData = 0xffffffff;
		rdc.WhiteTexture = Texture2D::create(1, 1,&WhiteTexData);

		int samplers[rdc.MaxTextureSlots];
		for (uint32_t i = 0; i < rdc.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		rdc.QuadShader = shader::create("assets/shaders/TextureShader.fsf");
		rdc.QuadShader->bind();
		rdc.QuadShader->UploadUniformIntArray("u_Textures",samplers, rdc.MaxTextureSlots);
		rdc.TextureSlots[0] = rdc.WhiteTexture;

		rdc.QuadVertexPositions[0] = { -0.5f , -0.5f , 0.0f , 1.0f };
		rdc.QuadVertexPositions[1] = {  0.5f , -0.5f , 0.0f , 1.0f };
		rdc.QuadVertexPositions[2] = {  0.5f ,  0.5f , 0.0f , 1.0f };
		rdc.QuadVertexPositions[3] = { -0.5f ,  0.5f , 0.0f , 1.0f };
		
	}

	void Renderer2D::Shutdown()
	{
		delete[] rdc.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene( const orthographic_camera& cam2d)
	{
		//rdc.TextureShader->bind();
	rdc.QuadShader->UploadUniformMat4("u_ViewProjectionMatrix", cam2d.GetViewProjectionMatrix());
		//rdc.TextureShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	
		StartBatch();
//	rdc.TextureShader->UploadUniformInt("u_Texture2", 1);
	
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)rdc.QuadVertexBufferPtr - (uint8_t*)rdc.QuadVertexBufferBase;
		rdc.QuadVB->SetData(rdc.QuadVertexBufferBase, dataSize);

		Clear();
	}
	void Renderer2D::StartBatch()
	{
		rdc.QuadIndexCount = 0;
		rdc.QuadVertexBufferPtr = rdc.QuadVertexBufferBase;
		
		//rdc.CircleIndexCount = 0;
	//	rdc.CircleVertexBufferPtr = s_Data.CircleVertexBufferBase;

	//	rdc.LineVertexCount = 0;
	//	rdc.LineVertexBufferPtr = s_Data.LineVertexBufferBase;
		
		rdc.TextureSlotIndex = 1;
	}
	void Renderer2D::Clear()
	{
	
		
		if (rdc.QuadIndexCount)
		{
			uint32_t dataSize = (uint32_t)((uint8_t*)rdc.QuadVertexBufferPtr - (uint8_t*)rdc.QuadVertexBufferBase);
			rdc.QuadVB->SetData(rdc.QuadVertexBufferBase, dataSize);

			// Bind textures
			for (uint32_t i = 0; i < rdc.TextureSlotIndex; i++)
				rdc.TextureSlots[i]->bind(i);

			rdc.QuadShader->bind();
			render_commands::drawElements(rdc.QuadVA, rdc.QuadIndexCount);
			//rdc.Stats.DrawCalls++;
		}

		  
		
	}
	void Renderer2D::RefreshBatch()
	{
		Clear();
		StartBatch();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
	
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform,color);
		
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const FRef<Texture2D>& texture, float TilingFactor, const glm::vec4 TintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture,TilingFactor,TintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const FRef<Texture2D>& texture, float TilingFactor, const glm::vec4 TintColor)
	{
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, TilingFactor, TintColor);


	}

	void Renderer2D::DrawTRSQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawTRSQuad({ position.x,position.y ,0.0f}, size, rotation, color);
	}

	void Renderer2D::DrawTRSQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 TextureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (rdc.QuadIndexCount >= Renderer2DData::MaxIndices)
			RefreshBatch();

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			rdc.QuadVertexBufferPtr->Position = transform * rdc.QuadVertexPositions[i];
			rdc.QuadVertexBufferPtr->Color = color;
			rdc.QuadVertexBufferPtr->TexCoord = TextureCoords[i];
			rdc.QuadVertexBufferPtr->TextureIndex = textureIndex;
			rdc.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			//rdc.QuadVertexBufferPtr->EntityID = entityID;
			rdc.QuadVertexBufferPtr++;
		}

		rdc.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const FRef<Texture2D>& texture, float TilingFactor, const glm::vec4 TintColor)
	{
		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (rdc.QuadIndexCount >= Renderer2DData::MaxIndices)
			RefreshBatch();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < rdc.TextureSlotIndex; i++)
		{
			if (*rdc.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (rdc.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				RefreshBatch();

			textureIndex = (float)rdc.TextureSlotIndex;
			rdc.TextureSlots[rdc.TextureSlotIndex] = texture;
			rdc.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			rdc.QuadVertexBufferPtr->Position = transform * rdc.QuadVertexPositions[i];
			rdc.QuadVertexBufferPtr->Color = TintColor;
			rdc.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			rdc.QuadVertexBufferPtr->TextureIndex = textureIndex;
			rdc.QuadVertexBufferPtr->TilingFactor = TilingFactor;
			//rdc.QuadVertexBufferPtr->EntityID = entityID;
			rdc.QuadVertexBufferPtr++;
		}

		rdc.QuadIndexCount += 6;

		//rdc.Stats.QuadCount++;
	}

#if ECS
	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		rdc.TextureShader->UploadUniformFloat4("u_Color", color);

		rdc.WhiteTexture->bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) /*rotation*/
			*glm::rotate(glm::mat4(1.0f),glm::radians(rotation),{0.0f,0.0f,1.0f})
			 * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		rdc.TextureShader->UploadUniformMat4("u_Transform", transform);
		rdc.QuadVA->bind();
		render_commands::drawElements(rdc.QuadVA);
	}
	
#endif
	
}