#include"frpch.h"
#include <fstream>
#include <cerrno>
#include"opengl_shader.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
namespace Forge {
	static GLenum ShaderTypeDetection(const FString& type)
	{
		if (type == "vertex") 
			return GL_VERTEX_SHADER;
		if (type == "pixel" || type == "fragment")
			return GL_FRAGMENT_SHADER;

		else FR_CORE_FATAL("Unknown Shader Type ");
		
	}

	OpenGLShader::OpenGLShader(const FString& filepath)
	{
		FString ShaderSource = ReadFile(filepath);
		auto ProcSource = ShaderPreProcess(ShaderSource);
		Compile(ProcSource);
	}
	//OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragSrc)
	//{
		//std::string vertexSource = // Get source code for vertex shader.
		//	std::string fragmentSource = // Get source code for fragment shader.

			// Create an empty vertex shader handle
	
	//}
	FString OpenGLShader::ReadFile(const FString& filepath)
	{
		FString contents;
		std::ifstream in(filepath, std::ios::in, std::ios::binary);
		if (in)
		{
			
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
		}
		else
		{
			FR_CORE_ERROR("Could not open Shader file '{0}'", filepath);
		}
		return contents;
	}
	std::unordered_map<GLenum, FString> OpenGLShader::ShaderPreProcess(const FString& source)
	{

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			FR_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			FR_CORE_ASSERT(ShaderTypeDetection(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			FR_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[ShaderTypeDetection(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}
	void OpenGLShader::Compile(const std::unordered_map<GLenum, FString>& sources)
	{
		GLuint program = glCreateProgram();
		std::vector<GLenum> shaderID(sources.size());
		for (auto& KeyVal : sources)
		{
			GLenum type = KeyVal.first;
			const FString& source = KeyVal.second;

			GLuint Shader = glCreateShader(type);
			const GLchar* source_cstr = (const GLchar*)source.c_str();
			glShaderSource(Shader, 1, &source_cstr, 0);

			// Compile the vertex shader
			glCompileShader(Shader);

			GLint isCompiled = 0;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(Shader);

				// Use the infoLog as you see fit.
				FR_CORE_ERROR("Vertex Shader compilation failed");
				FR_CORE_ERROR("{0}", infoLog.data());
				break;
			}
			glAttachShader(program, Shader);
			shaderID.push_back(Shader);
		}

	// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : shaderID)
			{
				glDeleteShader(id);
			}
			// Use the infoLog as you see fit.
			FR_CORE_ERROR(" Shader linking failed");
			FR_CORE_ERROR("{0}", infoLog.data());
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		for(auto id :shaderID)
			glDetachShader(program, id);
		m_rendererID = program;

	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_rendererID);
	}
	void OpenGLShader::bind() const
	{
		glUseProgram(m_rendererID);
	}
	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)const
	{
		GLint uniformLocation = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)const
	{
		GLint Location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform3f(Location, value.x, value.y, value.z);
	}
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)const
	{
		GLint Location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform4f(Location, value.x, value.y, value.z,value.w);
	}

	void OpenGLShader::UploadUniformInt(const FString& name, int value) const
	{
		GLint Location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1i(Location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const FString& name, int* values, uint32_t count)
	{
		GLint Location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1iv(Location, count, values);
	}

	

}