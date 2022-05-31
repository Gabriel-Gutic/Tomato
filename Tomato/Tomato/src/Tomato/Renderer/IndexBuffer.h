#pragma once
#include "Buffer.h"


namespace Tomato
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(std::initializer_list<UInt> indices);
		virtual ~IndexBuffer() override;

		UInt GetSize() const;

		virtual void Bind() override;
	private:
		UInt m_Size;
	};
}
