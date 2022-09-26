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
		mesh.Indices = { 0, 2, 1, 1, 2, 3 };
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
		mesh.Vertices = 
		{ 
			// Bottom
			Vertex(Float3(-0.5f, -0.5f, -0.5f), Float4(1.0f, 0.0f, 0.0f, 1.0f), Float3( 0.0f, -1.0f,  0.0f), Float2(0.0f, 0.0f)), //0
			Vertex(Float3( 0.5f, -0.5f, -0.5f), Float4(0.0f, 1.0f, 0.0f, 1.0f), Float3( 0.0f, -1.0f,  0.0f), Float2(1.0f, 0.0f)), //1
			Vertex(Float3( 0.5f, -0.5f,  0.5f), Float4(0.0f, 0.0f, 1.0f, 1.0f), Float3( 0.0f, -1.0f,  0.0f), Float2(1.0f, 1.0f)), //2
			Vertex(Float3(-0.5f, -0.5f,  0.5f), Float4(1.0f, 1.0f, 0.0f, 1.0f), Float3( 0.0f, -1.0f,  0.0f), Float2(0.0f, 1.0f)), //3
			// Left
			Vertex(Float3(-0.5f, -0.5f, -0.5f), Float4(1.0f, 0.0f, 0.0f, 1.0f), Float3(-1.0f,  0.0f,  0.0f), Float2(0.0f, 0.0f)), //4
			Vertex(Float3(-0.5f, -0.5f,  0.5f), Float4(1.0f, 1.0f, 0.0f, 1.0f), Float3(-1.0f,  0.0f,  0.0f), Float2(1.0f, 0.0f)), //5
			Vertex(Float3(-0.5f,  0.5f,  0.5f), Float4(0.0f, 0.0f, 0.0f, 1.0f), Float3(-1.0f,  0.0f,  0.0f), Float2(1.0f, 1.0f)), //6
			Vertex(Float3(-0.5f,  0.5f, -0.5f), Float4(0.0f, 1.0f, 1.0f, 1.0f), Float3(-1.0f,  0.0f,  0.0f), Float2(0.0f, 1.0f)), //7
			// Back
			Vertex(Float3(-0.5f, -0.5f, -0.5f), Float4(1.0f, 0.0f, 0.0f, 1.0f), Float3( 0.0f,  0.0f, -1.0f), Float2(1.0f, 0.0f)), //8
			Vertex(Float3( 0.5f, -0.5f, -0.5f), Float4(0.0f, 1.0f, 0.0f, 1.0f), Float3( 0.0f,  0.0f, -1.0f), Float2(0.0f, 0.0f)), //9
			Vertex(Float3(-0.5f,  0.5f, -0.5f), Float4(0.0f, 1.0f, 1.0f, 1.0f), Float3( 0.0f,  0.0f, -1.0f), Float2(1.0f, 1.0f)), //10
			Vertex(Float3( 0.5f,  0.5f, -0.5f), Float4(1.0f, 0.0f, 1.0f, 1.0f), Float3( 0.0f,  0.0f, -1.0f), Float2(0.0f, 1.0f)), //11
			// Right
			Vertex(Float3( 0.5f, -0.5f, -0.5f), Float4(0.0f, 1.0f, 0.0f, 1.0f), Float3( 1.0f,  0.0f,  0.0f), Float2(1.0f, 0.0f)), //12
			Vertex(Float3( 0.5f, -0.5f,  0.5f), Float4(0.0f, 0.0f, 1.0f, 1.0f), Float3( 1.0f,  0.0f,  0.0f), Float2(0.0f, 0.0f)), //13
			Vertex(Float3( 0.5f,  0.5f, -0.5f), Float4(1.0f, 0.0f, 1.0f, 1.0f), Float3( 1.0f,  0.0f,  0.0f), Float2(1.0f, 1.0f)), //14
			Vertex(Float3( 0.5f,  0.5f,  0.5f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3( 1.0f,  0.0f,  0.0f), Float2(0.0f, 1.0f)), //15
			// Front
			Vertex(Float3( 0.5f, -0.5f,  0.5f), Float4(0.0f, 0.0f, 1.0f, 1.0f), Float3( 0.0f,  0.0f,  1.0f), Float2(1.0f, 0.0f)), //16
			Vertex(Float3(-0.5f, -0.5f,  0.5f), Float4(1.0f, 1.0f, 0.0f, 1.0f), Float3( 0.0f,  0.0f,  1.0f), Float2(0.0f, 0.0f)), //17
			Vertex(Float3( 0.5f,  0.5f,  0.5f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3( 0.0f,  0.0f,  1.0f), Float2(1.0f, 1.0f)), //18
			Vertex(Float3(-0.5f,  0.5f,  0.5f), Float4(0.0f, 0.0f, 0.0f, 1.0f), Float3( 0.0f,  0.0f,  1.0f), Float2(0.0f, 1.0f)), //19
			// Top
			Vertex(Float3(-0.5f,  0.5f, -0.5f), Float4(0.0f, 1.0f, 1.0f, 1.0f), Float3( 0.0f,  1.0f,  0.0f), Float2(0.0f, 1.0f)), //20
			Vertex(Float3( 0.5f,  0.5f, -0.5f), Float4(1.0f, 0.0f, 1.0f, 1.0f), Float3( 0.0f,  1.0f,  0.0f), Float2(1.0f, 1.0f)), //21
			Vertex(Float3( 0.5f,  0.5f,  0.5f), Float4(1.0f, 1.0f, 1.0f, 1.0f), Float3( 0.0f,  1.0f,  0.0f), Float2(1.0f, 0.0f)), //22
			Vertex(Float3(-0.5f,  0.5f,  0.5f), Float4(0.0f, 0.0f, 0.0f, 1.0f), Float3( 0.0f,  1.0f,  0.0f), Float2(0.0f, 0.0f)), //23
		};
		mesh.Indices = 
		{ 
			2, 1, 0, 2, 0, 3,           // Bottom
			6, 5, 4, 6, 4, 7,			// Left
			10, 8, 9, 10, 9, 11,		// Back
			14, 12, 13, 14, 13, 15,		// Right
			18, 16, 17, 18, 17, 19,		// Front
			21, 22, 23, 21, 23, 20,		// Top
		};
		return mesh;
	}
}