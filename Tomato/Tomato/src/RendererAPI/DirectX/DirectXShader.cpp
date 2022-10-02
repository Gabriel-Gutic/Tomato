#include "pchTomato.h"
#include "DirectXShader.h"

#ifdef TOMATO_PLATFORM_WINDOWS
#include "DirectXDevice.h"

#include <d3d11.h>
#include <d3dcompiler.h>


namespace Tomato
{
    struct DirectXShaderData
    {
        ID3D11VertexShader* VertexShader;
        ID3DBlob* VertexBlob;
        ID3D11PixelShader* FragmentShader;
        ID3DBlob* FragmentBlob;
        ID3D11Buffer* ConstantBuffer;
        ID3D11InputLayout* Layout;
        ID3D11SamplerState* SamplerState;

        DirectXShaderData() 
            :VertexShader(nullptr), VertexBlob(nullptr), FragmentShader(nullptr),
            FragmentBlob(nullptr), ConstantBuffer(nullptr), Layout(nullptr),
            SamplerState(nullptr) {}
    };
    static DirectXShaderData Data;

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

        ID3DBlob* errorBlob = nullptr;

        // Compile de Vertex Shader
        auto vSource = String::ToWString(vertexSource);

        HRESULT hr = D3DCompileFromFile(vSource.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
            "main", profile,
            flags, 0, &Data.VertexBlob, &errorBlob);
        TOMATO_ASSERT(SUCCEEDED(hr), "Vertex Shader Error: {0}", (char*)errorBlob->GetBufferPointer());
        

        // Compile the Fragment Shader
        auto fSource = String::ToWString(fragmentSource);

        profile = (dev->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "ps_5_0" : "ps_4_0";
        hr = D3DCompileFromFile(fSource.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE,
            "main", profile,
            flags, 0, &Data.FragmentBlob, &errorBlob);
        TOMATO_ASSERT(SUCCEEDED(hr), "Fragment Shader Error: {0}", (char*)errorBlob->GetBufferPointer());

        // encapsulate both shaders into shader objects
        dev->CreateVertexShader(Data.VertexBlob->GetBufferPointer(), Data.VertexBlob->GetBufferSize(), NULL, &Data.VertexShader);
        dev->CreatePixelShader(Data.FragmentBlob->GetBufferPointer(), Data.FragmentBlob->GetBufferSize(), NULL, &Data.FragmentShader);

        TOMATO_ASSERT(Data.VertexShader, "Failed to create the Vertex Shader!");
        TOMATO_ASSERT(Data.FragmentShader, "Failed to create the Fragment Shader!");

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

        Data.ConstantBuffer = constantBuffer;

        // Sampler
        D3D11_SAMPLER_DESC ImageSamplerDesc = {};

        ImageSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        ImageSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        ImageSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        ImageSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        ImageSamplerDesc.MipLODBias = 0.0f;
        ImageSamplerDesc.MaxAnisotropy = 1;
        ImageSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        ImageSamplerDesc.BorderColor[0] = 1.0f;
        ImageSamplerDesc.BorderColor[1] = 1.0f;
        ImageSamplerDesc.BorderColor[2] = 1.0f;
        ImageSamplerDesc.BorderColor[3] = 1.0f;
        ImageSamplerDesc.MinLOD = -FLT_MAX;
        ImageSamplerDesc.MaxLOD = FLT_MAX;

        TOMATO_ASSERT(SUCCEEDED(dev->CreateSamplerState(&ImageSamplerDesc,
            &Data.SamplerState)), "Failed to create sampler for Directx Texture!");
	}

	DirectXShader::~DirectXShader()
	{
        Data.VertexShader->Release();
        Data.FragmentShader->Release();

        Data.VertexBlob->Release();
        Data.FragmentBlob->Release();

        Data.Layout->Release();
        Data.ConstantBuffer->Release();
	}

	void DirectXShader::Use()
	{
        auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());
        auto dev = std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice());
        devcon->VSSetShader(Data.VertexShader, 0, 0);
        devcon->PSSetShader(Data.FragmentShader, 0, 0);
        devcon->PSSetSamplers(0, 1, &Data.SamplerState);

        D3D11_INPUT_ELEMENT_DESC inputElementDescription[5] =
        {
            {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Float3), D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(Float3) + sizeof(Float4), D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TexCoords", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Float3) + sizeof(Float4) + sizeof(Float3), D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TexIndex", 0, DXGI_FORMAT_R32_FLOAT, 0, sizeof(Float3) + sizeof(Float4) + sizeof(Float3) + sizeof(Float2), D3D11_INPUT_PER_VERTEX_DATA, 0},
        };

        if (Data.Layout)
            Data.Layout->Release();
        dev->CreateInputLayout(inputElementDescription, 5, Data.VertexBlob->GetBufferPointer(), Data.VertexBlob->GetBufferSize(), &Data.Layout);
        devcon->IASetInputLayout(Data.Layout);
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
            devcon->Map(Data.ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
            //  Update the constant buffer here.
            memcpy(mappedResource.pData, &m_ConstantBufferData.VP, sizeof(m_ConstantBufferData));
            //  Reenable GPU access to the constant buffer data.
            devcon->Unmap(Data.ConstantBuffer, 0);

            devcon->VSSetConstantBuffers(0u, 1u, &Data.ConstantBuffer);
        }
	}
}

#endif // TOMATO_PLATFORM_WINDOWS
