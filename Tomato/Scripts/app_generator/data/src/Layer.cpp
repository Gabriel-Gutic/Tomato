#include "pch{ProjectName}.h"
#include "{ProjectName}Layer.h"


{ProjectName}Layer::{ProjectName}Layer()
{
}

void {ProjectName}Layer::OnUpdate(Tomato::Float dt)
{
}

void {ProjectName}Layer::OnEvent(const Tomato::Event& e)
{
}

void {ProjectName}Layer::OnGUI()
{
	ImGui::Begin("Example Window");
    ImGui::Text("Hello world!");
	ImGui::End();
}
