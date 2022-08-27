#pragma once


namespace Tomato
{
	class Mesh
	{
	public:
		std::vector<Float3> Vertices;
		std::vector<UInt> Indices;
		std::vector<Float2> TexCoords;

		Mesh() = default;
		Mesh(const Mesh&) = default;
		~Mesh() = default;

		std::vector<Float3> GetIndexedVertices() const;


		static Mesh TriangleMesh();
		static Mesh QuadMesh();
		static Mesh PolygonMesh(Int sides);
		static Mesh CircleMesh(Float smoothness);
	};
}
