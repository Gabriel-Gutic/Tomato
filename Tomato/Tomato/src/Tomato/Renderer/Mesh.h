#pragma once


namespace Tomato
{
	class Mesh
	{
	public:
		std::vector<Float3> Vertices;
		std::vector<unsigned int> Indices;
		std::vector<Float2> TexCoords;

		Mesh() = default;
		Mesh(const Mesh&) = default;
		~Mesh() = default;

		std::vector<Float3> GetIndexedVertices() const;


		static Mesh TriangleMesh();
		static Mesh QuadMesh();
		static Mesh PolygonMesh(int sides);
		static Mesh CircleMesh(float smoothness);
	};
}
