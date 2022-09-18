#pragma once
#include "Tomato/GUI/GUI_API.h"


namespace Tomato
{
	class DirectXGUI : public GUI_API
	{
		virtual void Initialize() override;
		virtual void Terminate() override;
		virtual void Begin() override;
		virtual void End() override;
	};
}