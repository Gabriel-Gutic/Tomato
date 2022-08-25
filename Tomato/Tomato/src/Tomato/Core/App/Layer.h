#pragma once
#include "Event/Event.h"


namespace Tomato
{
	class Layer
	{
	public:
		Layer(){}
		virtual ~Layer(){}

		virtual void OnUpdate(Float dt){}
		virtual void OnEvent(const Event& e){}
		virtual void OnGUI(){}
	};
}
