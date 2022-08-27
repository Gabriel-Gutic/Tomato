#include "pchTomato.h"
#include "Mesh.h"


namespace Tomato
{
	std::vector<Float3> Mesh::GetIndexedVertices() const
	{
		std::vector<Float3> result;
		result.resize(Indices.size());
		for (UInt i = 0; i < Indices.size(); i++)
		{
			result[i] = Vertices[Indices[i]];
		}

		return result;
	}

	Mesh Mesh::TriangleMesh()
	{
		Mesh mesh;
		mesh.Vertices = { Float3(0.0f, 0.5f, 0.0f), Float3(-0.5f, -0.5f, 0.0f), Float3(0.5f, -0.5f, 0.0f) };
		mesh.Indices = { 0, 1, 2 };
		mesh.TexCoords = { Float2(0.5f, 1.0f), Float2(0.0f, 0.0f), Float2(1.0f, 0.0f) };
		return mesh;
	}

	Mesh Mesh::QuadMesh()
	{
		Mesh mesh;
		mesh.Vertices = { Float3(-0.5f, -0.5f, 0.0f), Float3(0.5f, -0.5f, 0.0f), Float3(-0.5f, 0.5f, 0.0f), Float3(0.5f, 0.5f, 0.0f) };
		mesh.Indices = { 0, 1, 2, 1, 2, 3 };
		mesh.TexCoords = { Float2(0.0f, 1.0f), Float2(1.0f, 0.0f), Float2(0.0f, 1.0f), Float2(1.0f, 1.0f) };
		return mesh;
	}

	Mesh Mesh::PolygonMesh(Int sides)
	{
		TOMATO_ASSERT(sides >= 3, "You can't create a polygon with {0} sides", sides);
		Float angle = 360.0f / static_cast<Float>(sides);

		Mesh mesh;

		mesh.Vertices.reserve(sides + 1);

		mesh.Vertices.emplace_back();
		mesh.Vertices.emplace_back(0.0f, 0.5f);

		Float radius = 0.5f;
		Float2 center = Float2();
		Float t = acosf((mesh.Vertices[1].x - center.x) / radius);

		for (UInt i = 1; i < sides; i++)
		{
			mesh.Vertices.emplace_back(center.x + radius * cosf(t - Math::Radians(angle)), center.y + radius * sinf(t - Math::Radians(angle)));
			t -= Math::Radians(angle);
		}

		mesh.Indices.reserve(3 * sides);
		for (UInt i = 0; i < sides; i++)
		{
			mesh.Indices.push_back(0);
			mesh.Indices.push_back(i + 1);
			if (i + 2 > sides)
				mesh.Indices.push_back(1);
			else
				mesh.Indices.push_back(i + 2);
		}

		return mesh;
	}

	Mesh Mesh::CircleMesh(Float smoothness)
	{
		if (smoothness < 0.2f)
			smoothness = 0.2f;
		else if (smoothness > 1.0f)
			smoothness = 1.0f;
		return PolygonMesh(static_cast<UInt>(smoothness * 100));
	}
}