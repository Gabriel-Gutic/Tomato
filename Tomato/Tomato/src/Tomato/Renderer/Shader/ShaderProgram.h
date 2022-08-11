#pragma once


namespace Tomato
{
	class ShaderProgram
	{
	public:
		ShaderProgram(std::string_view vertexSource, std::string_view fragmentSource);
		~ShaderProgram();

		void Use(bool use = true);

		void SetUniformMat4(std::string_view location, const Mat4& matrix);
		template <size_t SIZE>
		void SetUniformIntArray(std::string_view location, const std::array<int, SIZE>& data) const;
		
		void SetUniformIntData(std::string_view location, UInt size, const int* data) const;

		UInt GetID() const;
		Int GetUniformLocation(std::string_view uniform) const;
	private:
		UInt m_RendererID;
		mutable std::unordered_map<std::string, Int> m_UniformLocations;
	};

	template <size_t SIZE>
	void ShaderProgram::SetUniformIntArray(std::string_view location, const std::array<int, SIZE>& data) const
	{
		SetUniformIntData(location, SIZE, data.data());
	}

}