#include "frpch.h"
#include "opengl_vertexArray.h"
#include "glad/glad.h"
namespace Forge {

	static GLenum sdtToGLtype(ShaderDataType type)
	{
		switch (type)
		{
		case Forge::ShaderDataType::FRfloat :  return GL_FLOAT;
		case Forge::ShaderDataType::FRfloat2:  return GL_FLOAT;
		case Forge::ShaderDataType::FRfloat3:  return GL_FLOAT;
		case Forge::ShaderDataType::FRfloat4:  return GL_FLOAT;
		case Forge::ShaderDataType::FRvec3 :   return GL_FLOAT;
		case Forge::ShaderDataType::FRvec4 :   return GL_FLOAT;
		case Forge::ShaderDataType::FRint  :   return GL_INT;
		case Forge::ShaderDataType::FRint2 :   return GL_INT;
		case Forge::ShaderDataType::FRint3 :   return GL_INT;
		case Forge::ShaderDataType::FRint4 :   return GL_INT;
		case Forge::ShaderDataType::FRbool:    return GL_BOOL;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_rendererID);

	}
	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_rendererID);
	}

	 void OpenGLVertexArray::unbind() const
	{
		 glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const FRef<vertex_buffer>& vb) 
	{
		glBindVertexArray(m_rendererID);
		vb->bind();
		uint32_t index = 0;
		const auto& layout = vb->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), sdtToGLtype(element.m_type), element.isNormalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.m_offset);

			index++;
		}
		m_vertexBuffers.push_back(vb);
	}
	void OpenGLVertexArray::SetIndexBuffer(const FRef<index_buffer>& ib)
	{

		glBindVertexArray(m_rendererID);
		ib->bind();
		m_indexBuffers = ib;
	}


}