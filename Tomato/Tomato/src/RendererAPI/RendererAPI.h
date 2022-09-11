#pragma once


namespace Tomato
{
	enum class RendererType
	{
		None = 0,
		OpenGL = 1,
		DirectX = 2
	};

	class RendererAPI
	{
		RendererAPI(){}
	public:
		static RendererType GetType();
		static void SetType(RendererType type);
	private:
		static RendererType s_Type;
	};
}
