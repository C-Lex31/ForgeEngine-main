#include "frpch.h"
#include "Renderer3D.h"
#include "core/servers/rendering/renderer/Renderer3D.h"
#include "core/servers/rendering/core_rd/shader.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Forge {

	struct Render3DData
	{
		FRef<vertex_array> PyroVA;
		FRef<vertex_array> CubeVA;
		FRef<vertex_array> PlaneVA;
		FRef<shader> PlaneShader;
		FRef<shader> CubeShader;
		FRef<shader> PyroTexShader;
	};
	static Render3DData* rdc;
	void Renderer3D::Init()
	{
		rdc = new Render3DData();

		rdc->PlaneVA = vertex_array::create();
		float PlaneVert[] = {
		//	------VERTICES---  ---TEXCOORD   ----NORMALS---
			-0.5f,0.0f, 0.5f,	0.0f,0.0f,   0.0f,1.0f,0.0f,
			-0.5f,0.0f,-0.5f,	0.0f,1.0f,	 0.0f,1.0f,0.0f,
			 0.5f,0.0f,-0.5f,	1.0f,1.0f,   0.0f,1.0f,0.0f,
			 0.5f,0.0f, 0.5f,	1.0f,0.0f,   0.0f,1.0f,0.0f
		};
		FRef<vertex_buffer>PlaneBuffer= vertex_buffer::create(PlaneVert, sizeof(PlaneVert));
		buffer_layout PlaneLayout = {
			{"a_Pos" ,ShaderDataType::FRfloat3},
			{"a_TexCoord",ShaderDataType::FRfloat2},
			{"a_Normal",ShaderDataType::FRfloat3}
		};
		PlaneBuffer->SetLayout(PlaneLayout);
		rdc->PlaneVA->AddVertexBuffer(PlaneBuffer);

		uint32_t PlaneIndices[] = {
			0,1,2,
			0,2,3
		};

		FRef<index_buffer>PlaneIB=index_buffer::create(PlaneIndices, sizeof(PlaneIndices) / sizeof(uint32_t));
		rdc->PlaneVA->SetIndexBuffer(PlaneIB);

		rdc->PyroVA = vertex_array::create();
		float vertices[] = {
			//-----VERTICES---      ----TEXCOORD-----  
		/*	-0.5f, 0.0f,  0.5f,      0.0f,0.0f,
			-0.5f, 0.0f, -0.5f,      5.0f,0.0f,		   
			0.5f,  0.0f, -0.5f,      0.0f,0.0f,		   
			0.5f , 0.0f,  0.5f,    	 5.0f,0.0f,		   
			0.0f , 0.8f,  0.0f,      2.5f,5.0f,		*/   
			//     COORDINATES        /    TexCoord   /        NORMALS       //
			-0.5f, 0.0f,  0.5f,    	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
			-0.5f, 0.0f, -0.5f,   	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
			 0.5f, 0.0f, -0.5f,   	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
			 0.5f, 0.0f,  0.5f,   	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

			-0.5f, 0.0f,  0.5f,    	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
			-0.5f, 0.0f, -0.5f,   	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
			 0.0f, 0.8f,  0.0f,   	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

			-0.5f, 0.0f, -0.5f,   	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
			 0.5f, 0.0f, -0.5f,   	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
			 0.0f, 0.8f,  0.0f,   	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

			 0.5f, 0.0f, -0.5f,   	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
			 0.5f, 0.0f,  0.5f,   	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
			 0.0f, 0.8f,  0.0f,   	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

			 0.5f, 0.0f,  0.5f,   	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
			-0.5f, 0.0f,  0.5f,    	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
			 0.0f, 0.8f,  0.0f,   	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
		};

		FRef<vertex_buffer>m_vertexBuffer=vertex_buffer::create(vertices, sizeof(vertices));
		buffer_layout layout = {
			{"aPos" ,ShaderDataType::FRfloat3},
			{"a_TexCoord",ShaderDataType::FRfloat2},
			{"a_Normal",ShaderDataType::FRfloat3}
		};

		m_vertexBuffer->SetLayout(layout);
		rdc->PyroVA->AddVertexBuffer(m_vertexBuffer);

		uint32_t indices[] = {
		/*	0,1,2,
			0,2,3,
			0,1,4,
			1,2,4,
			2,3,4,
			3,0,4*/
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
		};
		FRef<index_buffer>m_indexBuffer= index_buffer::create(indices, sizeof(indices) / sizeof(uint32_t));
		rdc->PyroVA->SetIndexBuffer(m_indexBuffer);

		rdc->CubeVA = vertex_array::create();
		float CubeVert[] = {
			// front
			 -0.5, -0.5f,  0.5f,	//1.0,0.0,0.0,1.0,        
			 0.5f, -0.5f,  0.5f,	//1.0,0.0,0.0,1.0,
			 0.5f,  0.5f,  0.5f,	//1.0,0.0,0.0,1.0,
			-0.5f,  0.5f,  0.5f,	//1.0,0.0,0.0,1.0,
			// back
			-0.5f, -0.5f, -0.5f,	//1.0,0.0,0.0,1.0,
			 0.5f, -0.5f, -0.5f,	//1.0,0.0,0.0,1.0,
			 0.5f,  0.5f, -0.5f,	//1.0,0.0,0.0,1.0,
			-0.5f,  0.5f, -0.5f,	//1.0,0.0,0.0,1.0
	/*-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f*/


		};
		FRef<vertex_buffer>CubeVB =vertex_buffer::create(CubeVert, sizeof(CubeVert));
		buffer_layout CubeLayout = {
			{"a_Pos" ,ShaderDataType::FRfloat3},
		//	{"a_Color",ShaderDataType::FRfloat4}
		};
		CubeVB->SetLayout(CubeLayout);
		rdc->CubeVA->AddVertexBuffer(CubeVB);

		uint32_t CubeIndices[] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		/*	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7*/

		};
		FRef<index_buffer> CubeIB =index_buffer::create(CubeIndices, sizeof(CubeIndices) / sizeof(uint32_t));
		rdc->CubeVA->SetIndexBuffer(CubeIB);

		rdc->CubeShader = shader::create("assets/shaders/CubeShader.fsf");
		rdc->PyroTexShader = shader::create("assets/shaders/PyramidTextureShader.fsf");
		rdc->PlaneShader = shader::create("assets/shaders/PlaneShader.fsf");
	}

	void Renderer3D::Shutdown()
	{
		delete rdc;
	}

	void Renderer3D::BeginScene(const Camera& cam )
	{
		glm::mat4 model = glm::mat4(1.0f);
		rdc->PyroTexShader->bind();
		rdc->PyroTexShader->UploadUniformMat4("u_ViewProjectionMatrix", cam.GetViewProjectionMatrix());
		rdc->PyroTexShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
		rdc->PyroTexShader->UploadUniformInt("u_Texture", 0);
		rdc->PyroTexShader->UploadUniformFloat3("u_CamPos", cam.GetCamPos());
	//  glm::vec3 fuck = cam.GetCamPos();
	//	FR_TRACE("{0} ,{1}, {2}", fuck.x ,fuck.y ,fuck.z);
		rdc->CubeShader->bind();
		rdc->CubeShader->UploadUniformMat4("u_ViewProjectionMatrix", cam.GetViewProjectionMatrix());
		rdc->CubeShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));

		rdc->PlaneShader->bind();
		rdc->PlaneShader->UploadUniformMat4("u_ViewProjectionMatrix", cam.GetViewProjectionMatrix());
		rdc->PlaneShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
		rdc->PlaneShader->UploadUniformInt("u_Texture",0);
		rdc->PlaneShader->UploadUniformInt("u_SpecMap", 1);
		rdc->PlaneShader->UploadUniformFloat3("u_CamPos", cam.GetCamPos());
	}

	void Renderer3D::EndScene()
	{
	}
	void Renderer3D::DrawPlane(const glm::vec3& position, const glm::vec3& size, const FRef<Texture2D>& texture, const FRef<Texture2D>& SpecularMap, const glm::vec4& color,const glm::vec3& LightPos, const glm::mat4& model)
	{
		rdc->PlaneShader->bind();
		rdc->PlaneShader->UploadUniformFloat4("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) */*rotation*/
			glm::scale(glm::mat4(1.0f), { size.x,size.y,size.z });
		rdc->PlaneShader->UploadUniformMat4("u_Transform", transform);
		rdc->PlaneShader->UploadUniformMat4("model", model);
		rdc->PlaneShader->UploadUniformFloat3("u_LightPos", LightPos);
		texture->bind(0);
		SpecularMap->bind(1);
	
		
	  
		rdc->PlaneVA->bind();
		render_commands::drawElements(rdc->PlaneVA);
	}
	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const glm::mat4& model)
	{
		rdc->CubeShader->bind();
		rdc->CubeShader->UploadUniformFloat4("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,size.z });
		rdc->CubeShader->UploadUniformMat4("u_Transform", transform);
		rdc->CubeShader->UploadUniformMat4("model", model);
		
		rdc->CubeVA->bind();
		render_commands::drawElements(rdc->CubeVA);
	}

	void Renderer3D::DrawPyramid(const glm::vec3& position, const glm::vec3& size, const FRef<Texture2D>& texture, const glm::vec4 LightColor , const glm::vec3& LightPos, const glm::mat4& model)
	{
		rdc->PyroTexShader->bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) */*rotation*/
			glm::scale(glm::mat4(1.0f), { size.x,size.y,size.z });
		rdc->PyroTexShader->UploadUniformMat4("u_Transform", transform);
		rdc->PyroTexShader->UploadUniformMat4("model", model);
		rdc->PyroTexShader->UploadUniformFloat4("u_Color", LightColor);
		rdc->PyroTexShader->UploadUniformFloat3("u_LightPos", LightPos);
		texture->bind();
		rdc->PyroVA->bind();
		render_commands::drawElements(rdc->PyroVA);
	}

}