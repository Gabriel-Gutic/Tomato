#pragma once


namespace Tomato
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		static void Unbind();
	private:
		unsigned int m_RendererID;
	};
}
