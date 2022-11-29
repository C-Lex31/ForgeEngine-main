#pragma once

#include "core/servers/rendering/core_rd/render_commands.h"
#include "core/servers/camera/3D/controller_main.h"
#include "core/servers/rendering/core_rd/texture.h"
namespace Forge {

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& cam  );
		static void EndScene();
		static void Clear();

		static void DrawPlane(const glm::vec3& position, const glm::vec3& size, const FRef<Texture2D>& texture, const FRef<Texture2D>& SpecularMap, const glm::vec4& color, const glm::vec3& LightPos, const glm::mat4& model = glm::mat4(1.0f));
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const glm::mat4& model = glm::mat4(1.0f));
		static void DrawPyramid(const glm::vec3& position, const glm::vec3& size, const FRef<Texture2D>& texture, const glm::vec4 LightColor, const glm::vec3& LightPos, const glm::mat4& model = glm::mat4(1.0f));

	private:
		static void StartBatch();
		static void RefreshBatch();
	};

}

