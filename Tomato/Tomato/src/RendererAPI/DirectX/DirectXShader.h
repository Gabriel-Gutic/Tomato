#pragma once
#include "Tomato/Renderer/Shader.h"


namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS

	class DirectXShader : public Shader
	{
	public:
		DirectXShader(std::string_view vertexSource, std::string_view fragmentSource);
		virtual ~DirectXShader() override;

		virtual void Use() override;

		virtual void SetMat4(std::string_view location, const Mat4& matrix) override;

		virtual void SetIntData(std::string_view location, unsigned int size, const int* data) override;
	private:
		std::any m_VertexShader;
		std::any m_VertexBlob;
		std::any m_FragmentShader;
		std::any m_FragmentBlob;
		std::any m_ConstantBuffer;
		std::any m_Layout;
		struct 
		{
			Mat4 VP;
		} m_ConstantBufferData;
	};
#else
	class DirectXShader : public Shader
	{
	public:
		DirectXShader(std::string_view vertexSource, std::string_view fragmentSource){}
		virtual ~DirectXShader() override {}

		virtual void Use() override {}

		virtual void SetMat4(std::string_view location, const Mat4& matrix) override {}

		virtual void SetIntData(std::string_view location, unsigned int size, const int* data) override {}
	};
#endif // TOMATO_PLATFORM_WINDOWS
}
