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
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Use(bool use = true) const = 0;

		virtual void SetFloat(std::string_view location, float value) const = 0;
		virtual void SetFloat2(std::string_view location, const Float2& vec) const = 0;
		virtual void SetFloat3(std::string_view location, const Float3& vec) const = 0;
		virtual void SetFloat4(std::string_view location, const Float4& vec) const = 0;
		virtual void SetInt(std::string_view location, int value) const = 0;
		virtual void SetInt2(std::string_view location, const Int2& vec) const = 0;
		virtual void SetInt3(std::string_view location, const Int3& vec) const = 0;
		virtual void SetInt4(std::string_view location, const Int4& vec) const = 0;
		virtual void SetMat4(std::string_view location, const Mat4& matrix) const = 0;
		
		template <size_t SIZE>
		void SetIntArray(std::string_view location, const std::array<int, SIZE>& data) const;
		virtual void SetIntData(std::string_view location, unsigned int size, const int* data) const = 0;
	public:
		static std::unique_ptr<Shader> CreateUnique(std::string_view vertexSource, std::string_view fragmentSource);
		static std::shared_ptr<Shader> CreateShared(std::string_view vertexSource, std::string_view fragmentSource);
	protected:
		virtual unsigned int CompileShader(std::string_view source, ShaderType type) = 0;
		static std::string TypeToString(ShaderType type);
	};

	template <size_t SIZE>
	void Shader::SetIntArray(std::string_view location, const std::array<int, SIZE>& data) const
	{
		SetIntData(location, SIZE, data.data());
	}

}