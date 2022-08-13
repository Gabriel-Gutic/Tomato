#pragma once
#include "Transform.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	class Object
	{
	public:
		Object() = default;
		Object(std::string_view name);
		virtual ~Object() = default;

		void SetName(std::string_view name);
		const std::string& GetName() const;
	protected:
		std::string m_Name;
	};
}
