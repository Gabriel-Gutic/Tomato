#pragma once
#include "Object.h"


namespace Tomato
{
	class Quad : public Object<4>
	{
	public:
		Quad();
		virtual ~Quad() override;

		virtual std::vector<UInt> GetIndices() const override;
	};
}
