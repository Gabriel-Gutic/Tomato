#pragma once
#include "Event/Event.h"


namespace Tomato
{
	class Layer
	{
	public:
		Layer(){}

		virtual void OnUpdate(){}
		virtual void OnEvent(Event& e){}
		virtual void OnGUI(){}
	};
}
