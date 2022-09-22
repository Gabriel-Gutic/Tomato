#include "pchTomato.h"
#include "DirectXRenderer3D.h"

#ifdef TOMATO_PLATFORM_WINDOWS
#include "RendererAPI/RendererData.h"
#include "DirectXDevice.h"
#include "Tomato/Core/App/App.h"


#include <d3d11.h>


namespace Tomato
{
	struct DirectXRendererData
	{
		std::array<Mesh::Vertex, MAX_VERTEX_NUMBER> Vertices;
		uint32_t VertexCounter = 0;
		std::array<uint32_t, MAX_INDEX_NUMBER> Indices;
		uint32_t IndexCounter = 0;
	};
	static DirectXRendererData RendererData;

	DirectXRenderer3D::DirectXRenderer3D()
	{
		DirectXDevice::Initialize();

		struct Vertex
		{
			Float3 Position;
			Float4 Color;
		};

		m_Shader = std::move(Shader::CreateUnique("assets/Shaders/3D/VertexShader.hlsl", "assets/Shaders/3D/FragmentShader.hlsl"));
		m_VertexBuffer = std::move(VertexBuffer::CreateUnique(sizeof(RendererData.Vertices), BufferAllocType::Dynamic, RendererData.Vertices.data()));
		m_IndexBuffer = std::move(IndexBuffer::CreateUnique(RendererData.Indices.size(), BufferAllocType::Dynamic, RendererData.Indices.data()));
	}

	DirectXRenderer3D::~DirectXRenderer3D()
	{
		DirectXDevice::Terminate();
	}

	void DirectXRenderer3D::Begin()
	{
		m_Shader->Use();
		m_Shader->SetMat4("VP", Math::Transpose(App::GetCurrentScene()->GetViewProjection()));
	}

	void DirectXRenderer3D::End()
	{
		Flush();
	}

	void DirectXRenderer3D::Clear(float r, float g, float b, float a) const
	{
		Clear(Float4(r, g, b, a));
	}

	void DirectXRenderer3D::Clear(const Float4& color) const
	{
		DirectXDevice::Clear(color);
	}

	void DirectXRenderer3D::Swap() const
	{
		DirectXDevice::Swap();
	}

	void DirectXRenderer3D::Draw(const Mesh& mesh, const Mat4& transform)
	{
		if (RendererData.VertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			RendererData.IndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER)
			Flush();
		if (RendererData.VertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			RendererData.IndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER)
			return;

		for (const auto& index : mesh.Indices)
		{
			RendererData.Indices[RendererData.IndexCounter++] = RendererData.VertexCounter + index;
		}

		for (auto vertex : mesh.Vertices)
		{
			vertex.Position = (transform * Float4(vertex.Position, 1.0f)).xyz;
			RendererData.Vertices[RendererData.VertexCounter++] = vertex;
		}
	}

	void DirectXRenderer3D::Flush()
	{
		m_VertexBuffer->SetData(RendererData.Vertices, RendererData.VertexCounter);
		m_VertexBuffer->Bind();

		m_IndexBuffer->SetData(RendererData.Indices, RendererData.IndexCounter);
		m_IndexBuffer->Bind();

		auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());
		devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Draw without the index buffer
		// devcon->Draw(3, 0);
		// Draw within the index buffer
		devcon->DrawIndexed(RendererData.IndexCounter, 0, 0);

		RendererData.VertexCounter = 0;
		RendererData.IndexCounter = 0;
	}
}

#endif // TOMATO_PLATFORM_WINDOWS
