#include "pchTomato.h"
#include "Serializer.h"

#include "Renderer/Scene/Component/Component.h"


namespace Tomato
{
	Serializer::Serializer(std::string_view filePath)
		:m_FilePath(filePath)
	{
		if (!File::Exist(m_FilePath))
		{
			File file = File(m_FilePath, FileType::Write);
			file.Close();
		}
	}

	void Serializer::EncodeFloat2(YAML::Emitter& out, const Float2& f2)
	{
		out << YAML::BeginSeq << f2.x << f2.y << YAML::EndSeq;
	}

	void Serializer::EncodeFloat3(YAML::Emitter& out, const Float3& f3)
	{
		out << YAML::BeginSeq << f3.x << f3.y << f3.z << YAML::EndSeq;
	}

	void Serializer::EncodeFloat4(YAML::Emitter& out, const Float4& f4)
	{
		out << YAML::BeginSeq << f4.x << f4.y << f4.z << f4.w << YAML::EndSeq;
	}

	Float2 Serializer::DecodeFloat2(const YAML::Node& node)
	{
		if (!node.IsSequence() or node.size() != 2)
		{
			TOMATO_ERROR("Invalid Node");
			return Float2();
		}

		return Float2(node[0].as<Float>(), node[1].as<Float>());
	}

	Float3 Serializer::DecodeFloat3(const YAML::Node& node)
	{
		if (!node.IsSequence() or node.size() != 3)
		{
			TOMATO_ERROR("Invalid Node");
			return Float3();
		}

		return Float3(node[0].as<Float>(), node[1].as<Float>(), node[2].as<Float>());
	}

	Float4 Serializer::DecodeFloat4(const YAML::Node& node)
	{
		if (!node.IsSequence() or node.size() != 4)
		{
			TOMATO_ERROR("Invalid Node");
			return Float4();
		}

		return Float4(node[0].as<Float>(), node[1].as<Float>(), node[2].as<Float>(), node[3].as<Float>());
	}

	void Serializer::EncodeTransform(YAML::Emitter& out, const TransformComponent& tran)
	{
		out << YAML::Key << "Transform" << YAML::Value << YAML::BeginMap;
		out << YAML::Key << "Position" << YAML::Value;
		EncodeFloat3(out, tran.Position);
		out << YAML::Key << "Scale" << YAML::Value;
		EncodeFloat3(out, tran.Scale);
		out << YAML::Key << "Rotation" << YAML::Value;
		EncodeFloat3(out, tran.Rotation);
		out << YAML::EndMap;
	}

	void Serializer::EncodeMeshRenderer(YAML::Emitter& out, const MeshRendererComponent& rend)
	{
		out << YAML::Key << "MeshRenderer" << YAML::Value << YAML::BeginMap;
		out << YAML::Key << "Sprite" << YAML::Value << rend.Sprite;
		out << YAML::Key << "Color" << YAML::Value;
		EncodeFloat4(out, rend.Color);
		out << YAML::Key << "Vertices" << YAML::Value << YAML::BeginSeq;
		for (const auto& vertex : rend.mesh.Vertices)
		{
			EncodeFloat3(out, vertex);
		}
		out << YAML::EndSeq;
		out << YAML::Key << "Indices" << YAML::Value << YAML::BeginSeq;
		for (const auto& index : rend.mesh.Indices)
		{
			out << index;
		}
		out << YAML::EndSeq;
		out << YAML::Key << "TexCoords" << YAML::Value << YAML::BeginSeq;
		for (const auto& texCoords : rend.mesh.TexCoords)
		{
			EncodeFloat2(out, texCoords);
		}
		out << YAML::EndSeq;
		out << YAML::EndMap;
	}

	void Serializer::EncodeCamera(YAML::Emitter& out, const CameraComponent& cam)
	{
		out << YAML::Key << "Camera" << YAML::Value << YAML::BeginMap;
		out << YAML::Key << "Target" << YAML::Value;
		EncodeFloat3(out, cam.Target);

		out << YAML::Key << "Perspective" << YAML::Value << YAML::BeginMap
			<< YAML::Key << "FOV" << YAML::Value << cam.Perspective.FOV
			<< YAML::Key << "AspectRatio" << YAML::Value << cam.Perspective.AspectRatio
			<< YAML::Key << "Near" << YAML::Value << cam.Perspective.Near
			<< YAML::Key << "Far" << YAML::Value << cam.Perspective.Far
			<< YAML::EndMap;
		out << YAML::Key << "Ortho" << YAML::Value << YAML::BeginMap
			<< YAML::Key << "Left" << YAML::Value << cam.Ortho.Left
			<< YAML::Key << "Right" << YAML::Value << cam.Ortho.Right
			<< YAML::Key << "Bottom" << YAML::Value << cam.Ortho.Bottom
			<< YAML::Key << "Top" << YAML::Value << cam.Ortho.Top
			<< YAML::Key << "Near" << YAML::Value << cam.Ortho.Near
			<< YAML::Key << "Far" << YAML::Value << cam.Ortho.Far
			<< YAML::EndMap;
		out << YAML::EndMap;
	}

	TransformComponent Serializer::DecodeTransform(const YAML::Node& node)
	{
		if (!node.IsMap())
		{
			TOMATO_ERROR("Invalid Node");
		}
		TransformComponent tran;
		auto& pos = node["Position"];
		if (pos)
			tran.Position = DecodeFloat3(pos);
		auto& scale = node["Scale"];
		if (scale)
			tran.Scale = DecodeFloat3(scale);
		auto& rot = node["Rotation"];
		if (rot)
			tran.Rotation = DecodeFloat3(rot);
		
		return tran;
	}

	MeshRendererComponent Serializer::DecodeMeshRenderer(const YAML::Node& node)
	{
		if (!node.IsMap())
		{
			TOMATO_ERROR("Invalid Node");
		}
		MeshRendererComponent rend;

		auto& sprite = node["Sprite"];
		if (sprite)
			rend.Sprite = sprite.as<std::string>();
		auto& color = node["Color"];
		if (color)
			rend.Color = DecodeFloat4(color);
		auto& vertices = node["Vertices"];
		if (vertices)
		{
			for (YAML::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
				rend.mesh.Vertices.push_back(DecodeFloat3(*it));
			}
		}
		auto& indices = node["Indices"];
		if (indices)
		{
			for (YAML::const_iterator it = indices.begin(); it != indices.end(); ++it) {
				rend.mesh.Indices.push_back(it->as<UInt>());
			}
		}
		auto& texCoords = node["TexCoords"];
		if (texCoords)
		{
			for (YAML::const_iterator it = texCoords.begin(); it != texCoords.end(); ++it) {
				rend.mesh.TexCoords.push_back(DecodeFloat2(*it));
			}
		}
		return rend;
	}

	CameraComponent Serializer::DecodeCamera(const YAML::Node& node)
	{
		if (!node.IsMap())
		{
			TOMATO_ERROR("Invalid Node");
		}
		CameraComponent cam;

		auto& target = node["Target"];
		if (target)
			cam.Target = DecodeFloat3(target);
		auto& perspective = node["Perspective"];
		if (perspective)
		{
			auto& FOV = perspective["FOV"];
			if (FOV)
				cam.Perspective.FOV = FOV.as<Float>();
			auto& AspectRatio = perspective["AspectRatio"];
			if (AspectRatio)
				cam.Perspective.AspectRatio = AspectRatio.as<Float>();
			auto& Near = perspective["Near"];
			if (Near)
				cam.Perspective.Near = Near.as<Float>();
			auto& Far = perspective["Far"];
			if (Far)
				cam.Perspective.Far = Far.as<Float>();
		}

		auto& ortho = node["Ortho"];
		if (ortho)
		{
			auto& Left = ortho["Left"];
			if (Left)
				cam.Ortho.Left = Left.as<Float>();
			auto& Right = ortho["Right"];
			if (Right)
				cam.Ortho.Right = Right.as<Float>();
			auto& Top = ortho["Top"];
			if (Top)
				cam.Ortho.Top = Top.as<Float>();
			auto& Bottom = ortho["Bottom"];
			if (Bottom)
				cam.Ortho.Bottom = Bottom.as<Float>();
			auto& Near = ortho["Near"];
			if (Near)
				cam.Ortho.Near = Near.as<Float>();
			auto& Far = ortho["Far"];
			if (Far)
				cam.Ortho.Far = Far.as<Float>();
		}
		return cam;
	}
}