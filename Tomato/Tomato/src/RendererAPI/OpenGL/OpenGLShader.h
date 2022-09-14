#pragma once
#include "Tomato/Renderer/Shader.h"


namespace Tomato
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string_view vertexSource, std::string_view fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Use(bool use = true) const;

		virtual void SetFloat(std::string_view location, float value) const;
		virtual void SetFloat2(std::string_view location, const Float2& vec) const;
		virtual void SetFloat3(std::string_view location, const Float3& vec) const;
		virtual void SetFloat4(std::string_view location, const Float4& vec) const;
		virtual void SetInt(std::string_view location, int value) const;
		virtual void SetInt2(std::string_view location, const Int2& vec) const;
		virtual void SetInt3(std::string_view location, const Int3& vec) const;
		virtual void SetInt4(std::string_view location, const Int4& vec) const;
		virtual void SetMat4(std::string_view location, const Mat4& matrix) const;

		unsigned int GetID() const;
		int GetUniformLocation(std::string_view uniform) const;

		virtual void SetIntData(std::string_view location, unsigned int size, const int* data) const;
	protected:
		virtual unsigned int CompileShader(std::string_view source, ShaderType type);
	private:
		unsigned int m_RendererID;
		mutable std::unordered_map<std::string, int> m_UniformLocations;
	};
}
