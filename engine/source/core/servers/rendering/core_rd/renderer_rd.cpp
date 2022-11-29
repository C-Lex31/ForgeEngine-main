#include "frpch.h"
#include "renderer_rd.h"
#include "core/servers/rendering/renderer/Renderer2D.h"
#include "core/servers/rendering/renderer/Renderer3D.h"
namespace Forge {
	FScope<renderer::SceneData> renderer::m_SceneData = FCreateScope<renderer::SceneData>();

	void renderer::Init()
	{

		render_commands::Init();
		Renderer3D::Init();
		Renderer2D::Init();   
	}

	void renderer::Shutdown()
	{
		Renderer3D::Shutdown();
		Renderer2D::Shutdown();
	}

	void renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		render_commands::SetViewport(0, 0, width, height);
	}

	void renderer::IR_BeginScene(orthographic_camera& cam)
	 {
		 m_SceneData->ViewProjectionatrix = cam.GetViewProjectionMatrix();
	 }
	 void renderer::IR_BeginScene(Camera& cam)
	 {
		 m_SceneData->ViewProjectionatrix = cam.GetViewProjectionMatrix();
	 }
	 void renderer::IR_EndScene()
	 {

	 }
	 void renderer::IR_Submit(const FRef<vertex_array>& va, const FRef<shader>& sh, const glm::mat4& transform ,const glm::mat4& model)
	 {
		 sh->bind();
		 va->bind();
		 sh->UploadUniformMat4("u_ViewProjectionMatrix",m_SceneData->ViewProjectionatrix );
		 sh->UploadUniformMat4("u_Transform", transform);
		 sh->UploadUniformMat4("model", model);
		 render_commands::drawElements(va);
	 }
}