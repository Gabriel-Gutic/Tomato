#pragma once


class TrianglesLayer : public Tomato::Layer
{
public:
	TrianglesLayer();
	~TrianglesLayer() = default;

	virtual void OnUpdate(Tomato::Float dt) override;
private:
	std::vector<std::unique_ptr<Tomato::Entity>> m_Triangles;
	const Tomato::UInt m_TriangleCounter = 1000;
};
