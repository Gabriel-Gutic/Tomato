#pragma once
#include "Texture/Texture.h"


namespace Tomato
{
	class Mesh
	{
	public:
		struct Vertex
		{
			Float3 Position;
			Float4 Color;
			Float3 Normal;
			Float2 TexCoords;
			Vertex(const Float3& pos = Float3(0.0f, 0.0f, 0.0f), const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f), const Float3& normal = Float3(0.0f, 0.0f, 0.0f), const Float2& texCoords = Float2(0.0f, 0.0f))
				:Position(pos), Color(color), Normal(normal), TexCoords(texCoords) {}
		};
	public:
		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<std::shared_ptr<Texture>> Textures;

		Mesh() = default;
		Mesh(const Mesh&) = default;
		~Mesh() = default;

	public:
		static Mesh TriangleMesh();
		static Mesh QuadMesh();
		static Mesh PolygonMesh(int sides);
		static Mesh CircleMesh(float smoothness);

	public:
		static Mesh Cube();
	};
}
