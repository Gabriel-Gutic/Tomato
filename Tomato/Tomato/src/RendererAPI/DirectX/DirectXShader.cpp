#include "pchTomato.h"
#include "DirectXShader.h"

#ifdef TOMATO_PLATFORM_WINDOWS
#include "DirectXDevice.h"

#include <d3d11.h>
#include <d3dcompiler.h>


namespace Tomato
{
	DirectXShader::DirectXShader(std::string_view vertexSource, std::string_view fragmentSource)
	{
        // Shader compiling
        UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
        flags |= D3DCOMPILE_DEBUG;
#endif

        auto dev = std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice());
        auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());

        // Prefer higher CS shader profile when possible as CS 5.0 provides better performance on 11-class hardware.
        LPCSTR profile = (dev->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "vs_5_0" : "vs_4_0";

        ID3DBlob* vertexBlob = nullptr;
        ID3DBlob* fragmentBlob = nullptr;
        ID3DBlob* errorBlob = nullptr;

        // Compile de Vertex Shader
        auto vSource = String::ToWString(vertexSource);

        HRESULT hr = D3DCompileFromFile(vSource.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
            "main", profile,
            flags, 0, &vertexBlob, &errorBlob);
        TOMATO_ASSERT(!FAILED(hr), "Vertex Shader Error: {0}", (char*)errorBlob->GetBufferPointer());
        

        // Compile the Fragment Shader
        auto fSource = String::ToWString(fragmentSource);

        profile = (dev->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "ps_5_0" : "ps_4_0";
        hr = D3DCompileFromFile(fSource.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
            "main", profile,
            flags, 0, &fragmentBlob, &errorBlob);
        TOMATO_ASSERT(!FAILED(hr), "Fragment Shader Error: {0}", (char*)errorBlob->GetBufferPointer());

        ID3D11VertexShader* vs;
        ID3D11PixelShader* fs;
        
        // encapsulate both shaders into shader objects
        dev->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), NULL, &vs);
        dev->CreatePixelShader(fragmentBlob->GetBufferPointer(), fragmentBlob->GetBufferSize(), NULL, &fs);

        TOMATO_ASSERT(vs, "Failed to create the Vertex Shader!");
        TOMATO_ASSERT(fs, "Failed to create the Fragment Shader!");

        m_VertexShader = vs;
        m_FragmentShader = fs;

        m_VertexBlob = vertexBlob;
        m_FragmentBlob = fragmentBlob;

        Use();

        // Create the constant buffer
        m_ConstantBufferData.VP = Mat4(1.0f);

        D3D11_BUFFER_DESC cbd = {};
        cbd.Usage = D3D11_USAGE_DYNAMIC;
        cbd.ByteWidth = sizeof(m_ConstantBufferData);
        cbd.StructureByteStride = 0u;
        cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        cbd.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA csd = {};
        csd.pSysMem = &m_ConstantBufferData.VP;

        ID3D11Buffer* constantBuffer;
        dev->CreateBuffer(&cbd, &csd, &constantBuffer);
        devcon->VSSetConstantBuffers(0u, 1u, &constantBuffer);

        m_ConstantBuffer = constantBuffer;
	}

	DirectXShader::~DirectXShader()
	{
        std::any_cast<ID3D11VertexShader*>(m_VertexShader)->Release();
        std::any_cast<ID3D11PixelShader*>(m_FragmentShader)->Release();

        std::any_cast<ID3DBlob*>(m_VertexBlob)->Release();
        std::any_cast<ID3DBlob*>(m_FragmentBlob)->Release();

        std::any_cast<ID3D11InputLayout*>(m_Layout)->Release();

        std::any_cast<ID3D11Buffer*>(m_ConstantBuffer)->Release();
	}

	void DirectXShader::Use()
	{
        auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());
        auto dev = std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice());
        devcon->VSSetShader(std::any_cast<ID3D11VertexShader*>(m_VertexShader), 0, 0);
        devcon->PSSetShader(std::any_cast<ID3D11PixelShader*>(m_FragmentShader), 0, 0);

        D3D11_INPUT_ELEMENT_DESC inputElementDescription[] =
        {
            {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Float3), D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(Float3) + sizeof(Float4), D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TexCoords", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Float3) + sizeof(Float4) + sizeof(Float3), D3D11_INPUT_PER_VERTEX_DATA, 0},
        };

        ID3D11InputLayout* layout;
        try 
        {
            layout = std::any_cast<ID3D11InputLayout*>(m_Layout);
            if (layout)
                layout->Release();
        }
        catch (const std::bad_any_cast& error)
        {}
        auto vertexBlob = std::any_cast<ID3DBlob*>(m_VertexBlob);
        dev->CreateInputLayout(inputElementDescription, 4, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &layout);
        devcon->IASetInputLayout(layout);
        m_Layout = layout;
    }

	void DirectXShader::SetMat4(std::string_view location, const Mat4& matrix)
	{
        bool isChanged = false;
        if (location == "VP")
        {
            m_ConstantBufferData.VP = matrix;
            isChanged = true;
        }

        if (isChanged)
        {
            // Change the data from a Constant Buffer
            D3D11_MAPPED_SUBRESOURCE mappedResource = {};

            //  Disable GPU access to the constant buffer data
            auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());
            auto constantBuffer = std::any_cast<ID3D11Buffer*>(m_ConstantBuffer);
            devcon->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
            //  Update the constant buffer here.
            memcpy(mappedResource.pData, &m_ConstantBufferData.VP, sizeof(m_ConstantBufferData));
            //  Reenable GPU access to the constant buffer data.
            devcon->Unmap(constantBuffer, 0);

            devcon->VSSetConstantBuffers(0u, 1u, &constantBuffer);
        }
	}

	void DirectXShader::SetIntData(std::string_view location, unsigned int size, const int* data)
	{
        // TODO: Implementation
	}
}

#endif // TOMATO_PLATFORM_WINDOWS
