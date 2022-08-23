#pragma once


namespace Tomato
{
	class UUID
	{
	public:
		UUID();
		explicit UUID(uint32_t uuid);

		uint32_t Get() const { return m_Identifier; }

		bool operator==(const UUID& other) const;
		operator uint32_t() const { return m_Identifier; }
	private:
		uint32_t m_Identifier;
	};
}
