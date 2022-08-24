#pragma once
#include "Tomato.h"


class TrianglesLayer : public Tomato::Layer
{
public:
	TrianglesLayer();
	~TrianglesLayer() = default;

	virtual void OnUpdate() override;
private:
	std::vector<std::unique_ptr<Tomato::Triangle>> m_Triangles;
	const Tomato::UInt m_TriangleCounter = 500;
};
