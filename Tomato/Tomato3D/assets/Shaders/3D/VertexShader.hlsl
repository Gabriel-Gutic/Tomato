struct Output
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

Output main(float3 pos : Position, float4 color : Color)
{
    Output output;
    output.Position = float4(pos, 1.0f);
    output.Color = color;
    return output;
}
