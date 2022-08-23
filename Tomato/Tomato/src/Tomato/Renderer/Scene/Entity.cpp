#include "pchTomato.h"
#include "Entity.h"


namespace Tomato
{
	std::string Entity::ToString() const
	{
		return "<Tomato::Entity>";
	}

	const UUID& Entity::GetUUID() const
	{
		return m_UUID;
	}
}

