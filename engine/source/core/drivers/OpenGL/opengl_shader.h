#pragma once

#include "core/servers/rendering/core_rd/shader.h"
#include "glad/glad.h"

namespace Forge {


	class OpenGLShader : public shader
	{
	public:
		OpenGLShader(const FString& filepath);
	//	OpenGLShader(const std::string& vertexSrc, const std::string& fragSrc);
		virtual ~OpenGLShader() ;
		virtual void bind() const override;
		virtual void unbind() const override;


		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const override;
		virtual void UploadUniformInt(const FString& name, int value) const override;
		virtual void UploadUniformIntArray(const FString& name, int* values, uint32_t count) override;
	private:
		FString ReadFile(const FString& filepath);
		std::unordered_map<GLenum , FString> ShaderPreProcess(const FString& source);
		void Compile(const std::unordered_map<GLenum, FString>& source);
	private:
		uint32_t m_rendererID;
	};

}
