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
		UInt m_RendererID;
	};
}
