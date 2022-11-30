#pragma once


namespace Tomato
{
	class Line
	{
	public:
		struct Vertex
		{
			Float3 Position;
			Float4 Color;
			Vertex(const Float3& pos = Float3(0.0f, 0.0f, 0.0f), const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f))
				:Position(pos), Color(color) {}
		};
	};
}
