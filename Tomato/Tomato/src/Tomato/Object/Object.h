#pragma once
#include "Transform.h"
#include "Renderer/Buffer/Vertex.h"


namespace Tomato
{
	template <size_t COUNT>
	class Object : public TransformInterface, public VertexInterface<COUNT>
	{
	public:
		Object() = default;
		Object(std::string_view name);
		virtual ~Object() = default;

		void SetName(std::string_view name);
		const std::string& GetName() const;

		virtual std::vector<UInt> GetIndices() const = 0;
	protected:
		std::string m_Name;
	};

	template<size_t COUNT>
	inline Object<COUNT>::Object(std::string_view name)
		:m_Name(name)
	{
	}

	template<size_t COUNT>
	inline void Object<COUNT>::SetName(std::string_view name)
	{
		m_Name = name;
	}

	template<size_t COUNT>
	inline const std::string& Object<COUNT>::GetName() const
	{
		return m_Name;
	}
}
