#pragma once


namespace Tomato
{
	class OpenGLInput
	{
	public:
		static bool Keyboard(int key);
		static bool Mouse(int button);
		static Float2 MousePos();
	};
}
