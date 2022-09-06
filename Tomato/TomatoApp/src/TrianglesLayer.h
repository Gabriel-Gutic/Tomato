#pragma once


class TrianglesLayer : public Tomato::Layer
{
public:
	TrianglesLayer();
	~TrianglesLayer() = default;

	virtual void OnUpdate(float dt) override;
private:
	std::vector<std::unique_ptr<Tomato::Entity>> m_Triangles;
	const unsigned int m_TriangleCounter = 1000;
};
