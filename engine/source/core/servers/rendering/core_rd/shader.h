#pragma once
 #include <string>

#include <glm/glm.hpp>

namespace Forge {


	class shader
	{
	public:
		virtual ~shader()=default;
		virtual void bind() const=0;
		virtual void unbind() const=0;

		virtual void UploadUniformMat4(const FString& name, const glm::mat4& matrix) const= 0;
		virtual void UploadUniformFloat3(const FString& name, const glm::vec3& value) const = 0;
		virtual void UploadUniformFloat4(const FString& name, const glm::vec4& value) const= 0;
		virtual void UploadUniformInt(const FString& name, int value) const = 0;
		virtual void UploadUniformIntArray(const FString& name, int* values, uint32_t count) =0;
		static FRef<shader> create(const FString& filepath);
		//static FRef<shader> create(const FString& vertexSrc, const FString& fragSrc);
		

	};

}