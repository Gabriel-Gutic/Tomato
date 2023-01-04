#pragma once
#include "Tomato/Renderer/Shader.h"


namespace Tomato
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string_view vertexSource, std::string_view fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Use() override;

		virtual void SetMat4(std::string_view location, const Mat4& matrix) override;
		virtual void SetFloat(std::string_view location, float f) override;
		virtual void SetFloat2(std::string_view location, const Float2& f2) override;
		virtual void SetFloat3(std::string_view location, const Float3& f3) override;
		virtual void SetFloat4(std::string_view location, const Float4& f4) override;

		unsigned int GetID() const;
		int GetUniformLocation(std::string_view uniform) const;

		virtual void SetIntData(std::string_view location, unsigned int size, const int* data) override;
	protected:
		virtual unsigned int CompileShader(std::string_view source, ShaderType type) override;
	private:
		unsigned int m_RendererID;
		mutable std::unordered_map<std::string, int> m_UniformLocations;
	};
}
