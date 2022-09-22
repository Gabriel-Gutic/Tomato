struct Output
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

cbuffer Transform
{
    matrix VP;
};

Output main(float3 pos : Position, float4 color : Color, float3 normal : Normal, float2 texCoords : TexCoords)
{
    Output output;
    output.Position = mul(float4(pos, 1.0f), VP);
    output.Color = color;
    return output;
}
