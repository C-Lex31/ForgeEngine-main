#pragma once
#include "core/servers/camera/2D/orthographic_camera.h"
#include "core/servers/camera/CameraCore.h"
#include "core/servers/rendering/core_rd/render_commands.h"
#include "core/servers/rendering/core_rd/texture.h"
namespace Forge {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const orthographic_camera& cam2d);
		static void BeginScene(const CameraCore& cam ,const glm::mat4& transform);
		static void EndScene();
		static void Clear();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const FRef<Texture2D>& texture, float TilingFactor, const glm::vec4 = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const FRef<Texture2D>& texture, float TilingFactor, const glm::vec4 TintColor = glm::vec4(1.0f));

		static void DrawTRSQuad(const glm::vec2& position , const glm::vec2& size = glm::vec2(1.0f, 1.0f),float rotation = 0.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawTRSQuad(const glm::vec3& position, const glm::vec2& size,float rotation = 0.0f, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawTRSQuad(const FRef<Texture2D>& texture, const glm::vec2& position, const glm::vec2& size= glm::vec2(1.0f,1.0f), float rotation = 0.0f, float TilingFactor = 10.0f, const glm::vec4 = glm::vec4(1.0f));
		static void DrawTRSQuad(const FRef<Texture2D>& texture, const glm::vec3& position, const glm::vec2& size = glm::vec2(1.0f, 1.0f),float rotation = 0.0f,  float TilingFactor=10.0f, const glm::vec4 TintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::mat4& transform, const FRef<Texture2D>& texture, float TilingFactor , const glm::vec4 TintColor = glm::vec4(1.0f));

	private:
		static void StartBatch();
		static void RefreshBatch();
	};

}
