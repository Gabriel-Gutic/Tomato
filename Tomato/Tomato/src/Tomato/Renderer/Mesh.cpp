#include "pchTomato.h"
#include "Mesh.h"


namespace Tomato
{
	Mesh Mesh::TriangleMesh()
	{
		Mesh mesh;
		mesh.Vertices = { Vertex(Float3(0.0f, 0.5f, 0.0f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3(), Float2(0.5f, 1.0f)), 
			Vertex(Float3(-0.5f, -0.5f, 0.0f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3(), Float2(0.0f, 0.0f)), 
			Vertex(Float3(0.5f, -0.5f, 0.0f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3(), Float2(1.0f, 0.0f)) };
		mesh.Indices = { 0, 1, 2 };
		return mesh;
	}

	Mesh Mesh::QuadMesh()
	{
		Mesh mesh;
		mesh.Vertices = { 
			Vertex(Float3(-0.5f, -0.5f, 0.0f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3(), Float2(0.0f, 0.0f)),
			Vertex(Float3( 0.5f, -0.5f, 0.0f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3(), Float2(1.0f, 0.0f)),
			Vertex(Float3(-0.5f,  0.5f, 0.0f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3(), Float2(0.0f, 1.0f)),
			Vertex(Float3( 0.5f,  0.5f, 0.0f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3(), Float2(1.0f, 1.0f)) };
		mesh.Indices = { 0, 1, 2, 1, 2, 3 };
		return mesh;
	}

	Mesh Mesh::PolygonMesh(int sides)
	{
		TOMATO_ASSERT(sides >= 3, "You can't create a polygon with {0} sides", sides);
		float angle = 360.0f / static_cast<float>(sides);

		Mesh mesh;

		mesh.Vertices.reserve(sides + 1);

		mesh.Vertices.emplace_back();
		mesh.Vertices.emplace_back(0.0f, 0.5f, 0.0f);

		float radius = 0.5f;
		Float2 center = Float2();
		float t = acosf((mesh.Vertices[1].Position.x - center.x) / radius);

		for (unsigned int i = 1; i < sides; i++)
		{
			mesh.Vertices.emplace_back(center.x + radius * cosf(t - Math::Radians(angle)), center.y + radius * sinf(t - Math::Radians(angle)), 0.0f);
			t -= Math::Radians(angle);
		}

		mesh.Indices.reserve(3 * sides);
		for (unsigned int i = 0; i < sides; i++)
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

	Mesh Mesh::CircleMesh(float smoothness)
	{
		if (smoothness < 0.2f)
			smoothness = 0.2f;
		else if (smoothness > 1.0f)
			smoothness = 1.0f;
		return PolygonMesh(static_cast<unsigned int>(smoothness * 100));
	}

	Mesh Mesh::Cube()
	{
		Mesh mesh;
		mesh.Vertices = { 
			Vertex(Float3(-0.5f, -0.5f, -0.5f), Float4(1.0f, 0.0f, 0.0f, 1.0f)),
			Vertex(Float3( 0.5f, -0.5f, -0.5f), Float4(0.0f, 1.0f, 0.0f, 1.0f)),
			Vertex(Float3( 0.5f, -0.5f,  0.5f), Float4(0.0f, 0.0f, 1.0f, 1.0f)),
			Vertex(Float3(-0.5f, -0.5f,  0.5f), Float4(1.0f, 1.0f, 0.0f, 1.0f)),
			Vertex(Float3(-0.5f,  0.5f, -0.5f), Float4(0.0f, 1.0f, 1.0f, 1.0f)),
			Vertex(Float3( 0.5f,  0.5f, -0.5f), Float4(1.0f, 0.0f, 1.0f, 1.0f)),
			Vertex(Float3( 0.5f,  0.5f,  0.5f), Float4(1.0f, 1.0f, 1.0f, 1.0f)),
			Vertex(Float3(-0.5f,  0.5f,  0.5f), Float4(0.0f, 0.0f, 0.0f, 1.0f)) };
		mesh.Indices = { 
			0, 2, 1, 2, 0, 3,
			3, 6, 2, 6, 3, 7,
			1, 5, 0, 4, 0, 5,
			1, 2, 6, 1, 6, 5,
			0, 4, 3, 3, 4, 7,
			4, 5, 6, 4, 6, 7,
		};
		return mesh;
	}
}