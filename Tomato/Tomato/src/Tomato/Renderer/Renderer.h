#pragma once
#include "Shader/ShaderProgram.h"


namespace Tomato
{
	class Renderer
	{
		Renderer(){}
	public:
		Renderer(const Renderer&) = delete;

		static void Initialize();
		static void Terminate();

		static void Begin();
		static void End();

		static Renderer* Get();
	private:
		std::unique_ptr<ShaderProgram> m_ShaderProgram;

		static Renderer* s_Instance;
	};
}

