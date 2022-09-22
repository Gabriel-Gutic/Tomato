#pragma once
#include "Tomato/GUI/GUI_API.h"


namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS
	class DirectXGUI : public GUI_API
	{
		virtual void Initialize() override;
		virtual void Terminate() override;
		virtual void Begin() override;
		virtual void End() override;
	};
#else
	class DirectXGUI : public GUI_API
	{
		virtual void Initialize() override {}
		virtual void Terminate() override {}
		virtual void Begin() override {}
		virtual void End() override {}
	};
#endif // TOMATO_PLATFORM_WINDOWS
}