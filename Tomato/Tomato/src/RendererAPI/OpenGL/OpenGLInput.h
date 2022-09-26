#pragma once


namespace Tomato
{
	class OpenGLInput
	{
		OpenGLInput() = delete;
	public:
		static bool Keyboard(int key);
		static bool Mouse(int button);
		static Float2 MousePos();

		static int ConvertNumPadKey(int key);
	};
}
