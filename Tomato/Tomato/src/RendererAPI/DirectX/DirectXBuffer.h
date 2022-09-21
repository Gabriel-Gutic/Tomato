#pragma once
#include "Tomato/Renderer/Buffer/Buffer.h"


namespace Tomato
{
	class DirectXBuffer
	{
	public:
		DirectXBuffer() = default;
		virtual ~DirectXBuffer() = default;
	protected:
		std::any m_Data;
	};
}
