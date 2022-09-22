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
