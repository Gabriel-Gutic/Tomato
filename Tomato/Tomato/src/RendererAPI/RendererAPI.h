#pragma once


namespace Tomato
{


	class RendererAPI
	{
	public:
		enum class Type
		{
			None = 0,
			OpenGL = 1,
			DirectX = 2
		};
		RendererAPI(){}
	public:
		static Type GetType();
		static void SetType(Type type);
	private:
		static Type s_Type;
	};
}
