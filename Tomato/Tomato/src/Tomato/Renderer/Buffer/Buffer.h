#pragma once


namespace Tomato
{
	class Buffer
	{
	public:
		Buffer();
		virtual ~Buffer();

		virtual void Bind() = 0;
		virtual void Unbind(){};
	protected:
		unsigned int m_RendererID;
	};
}