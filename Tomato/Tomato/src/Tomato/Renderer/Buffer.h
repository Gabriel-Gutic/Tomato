#pragma once


namespace Tomato
{
	class Buffer
	{
	public:
		Buffer();
		virtual ~Buffer();

		virtual void Bind() = 0;
	protected:
		UInt m_RendererID;
	};
}