#pragma once


namespace Tomato
{
	class UUID
	{
	public:
		UUID();
		explicit UUID(uint64_t uuid);

		uint64_t Get() const { return m_Identifier; }

		bool operator==(const UUID& other) const;
		operator uint64_t() const { return m_Identifier; }
	private:
		uint64_t m_Identifier;
	};
}
