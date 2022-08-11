#pragma once


namespace Tomato
{
	enum class ShaderType
	{
		Vertex = 0x8B31,
		Fragment = 0x8B30,
	};

	class Shader
	{
	public:
		Shader(std::string_view vertexSource, std::string_view fragmentSource);
		~Shader();

		void Use(bool use = true);

		void SetFloat(std::string_view location, Float value) const;
		void SetFloat2(std::string_view location, const Float2& vec) const;
		void SetFloat3(std::string_view location, const Float3& vec) const;
		void SetFloat4(std::string_view location, const Float4& vec) const;
		void SetInt(std::string_view location, Int value) const;
		void SetInt2(std::string_view location, const Int2& vec) const;
		void SetInt3(std::string_view location, const Int3& vec) const;
		void SetInt4(std::string_view location, const Int4& vec) const;
		void SetMat4(std::string_view location, const Mat4& matrix) const;
		
		template <size_t SIZE>
		void SetIntArray(std::string_view location, const std::array<int, SIZE>& data) const;
		void SetIntData(std::string_view location, UInt size, const int* data) const;

		UInt GetID() const;
		Int GetUniformLocation(std::string_view uniform) const;
	private:
		static UInt CompileShader(std::string_view source, ShaderType type);
		static const char* TypeToString(ShaderType type);
	private:
		UInt m_RendererID;
		mutable std::unordered_map<std::string, Int> m_UniformLocations;
	};

	template <size_t SIZE>
	void Shader::SetIntArray(std::string_view location, const std::array<int, SIZE>& data) const
	{
		SetIntData(location, SIZE, data.data());
	}

}