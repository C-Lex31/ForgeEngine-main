#pragma once

namespace Forge {

	enum class ShaderDataType
	{
		None=0,FRfloat,FRfloat2,FRfloat3,FRfloat4,FRvec3,FRvec4,FRint,FRint2,FRint3,FRint4,FRbool
	};

	static uint32_t sdtSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::FRfloat :   return 4;
			case ShaderDataType::FRfloat2:   return 4*2;
			case ShaderDataType::FRfloat3:   return 4*3;
			case ShaderDataType::FRfloat4:   return 4*4;
			case ShaderDataType::FRvec3  :   return 4*3*3;
			case ShaderDataType::FRvec4  :   return 4*4*4;
			case ShaderDataType::FRint   :   return 4;
			case ShaderDataType::FRint2  :   return 4*2;
			case ShaderDataType::FRint3  :   return 4*3;
			case ShaderDataType::FRint4  :   return 4*4;

		}

		return 0;
	}

	struct buffer_elements
	{
		std::string m_name;
		ShaderDataType m_type;
		uint32_t m_size;
		uint32_t m_offset;
		bool isNormalized;

		buffer_elements(const std::string& name,ShaderDataType type, bool normalized = false)
			:m_name(name),m_type(type),m_size(sdtSize(type)),m_offset(0),isNormalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (m_type)
			{
			case ShaderDataType::FRfloat:   return 1;
			case ShaderDataType::FRfloat2:  return 2;
			case ShaderDataType::FRfloat3:  return 3;
			case ShaderDataType::FRfloat4:  return 4;
			case ShaderDataType::FRvec3:    return 3; // 3* float3
			case ShaderDataType::FRvec4:    return 4; // 4* float4
			case ShaderDataType::FRint:     return 1;
			case ShaderDataType::FRint2:    return 2;
			case ShaderDataType::FRint3:    return 3;
			case ShaderDataType::FRint4:    return 4;
			case ShaderDataType::FRbool:    return 1;
			}
			return 0;
		}
	};


	class buffer_layout
	{
	public:
		buffer_layout() {}
		buffer_layout(const std::initializer_list<buffer_elements> element)
			:m_elements(element)
		{
			CalcOffsetStride();
		}
		inline uint32_t GetStride() const { return m_stride; }
		inline const std::vector<buffer_elements> getElements() const { return m_elements; }
		

		std::vector<buffer_elements>::iterator begin() { return m_elements.begin(); }
		std::vector<buffer_elements>::iterator end() { return m_elements.end(); }
		std::vector<buffer_elements>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<buffer_elements>::const_iterator end() const { return m_elements.end(); }
	
	private:
		void CalcOffsetStride()
		{
			uint32_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.m_offset = offset;
				offset += element.m_size;
				m_stride += element.m_size;
			}  
		}
	private:
		std::vector<buffer_elements> m_elements;
		uint32_t m_stride=0;
	};


	class vertex_buffer
	{
	public:
		virtual ~vertex_buffer() = default;
		virtual void bind() const=0;
		virtual void unbind() const= 0;
		virtual const buffer_layout& GetLayout()const = 0;
		virtual void SetLayout(const buffer_layout& layout) = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;

		static FRef<vertex_buffer> create(float* vertices , uint32_t size);
		static FRef<vertex_buffer> create( uint32_t size);
	};


	class index_buffer
	{
	public:
		virtual ~index_buffer() = default;
		virtual void bind() const=0;
		virtual void unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
		static FRef<index_buffer> create(uint32_t* indices, uint32_t count);
	};
	
}
