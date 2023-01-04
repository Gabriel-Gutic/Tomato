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
		virtual void SetFloat(std::string_view location, float f) override;
		virtual void SetFloat2(std::string_view location, const Float2& f2) override;
		virtual void SetFloat3(std::string_view location, const Float3& f3) override;
		virtual void SetFloat4(std::string_view location, const Float4& f4) override;
	private:
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
		virtual void SetFloat(std::string_view location, float f) override {}
		virtual void SetFloat2(std::string_view location, const Float2& f2) override {}
		virtual void SetFloat3(std::string_view location, const Float3& f3) override {}
		virtual void SetFloat4(std::string_view location, const Float4& f4) override {}

		virtual void SetIntData(std::string_view location, unsigned int size, const int* data) override {}
	};
#endif // TOMATO_PLATFORM_WINDOWS
}
