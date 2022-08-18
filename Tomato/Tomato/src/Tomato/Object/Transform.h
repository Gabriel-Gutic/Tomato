#pragma once


namespace Tomato
{
	struct Transform
	{
		Float3 Position;
		Float3 Scale;
		Float3 Rotation;

		Transform(const Float3& position = Float3(), const Float3& scale = Float3(1.0f, 1.0f, 1.0f), const Float3& rotation = Float3())
			:Position(position), Scale(scale), Rotation(rotation)
		{}

		Float3 Apply(const Float3& vector) const;
		void GUI(std::string_view headerName);
	};

	class TransformInterface
	{
	public:
		TransformInterface() = default;
		virtual ~TransformInterface() = default;

		void SetPosition(const Float3& position);
		void SetScale(const Float3& scale);
		void SetRotation(const Float3& rotation);
		const Float3& GetPosition() const;
		const Float3& GetScale() const;
		const Float3& GetRotation() const;

		void SetTransform(const Transform& tran);
		Transform& GetTransform();
		const Transform& GetTransform() const;
		virtual Float3 TransformCoords(const Float3& vector) const;
	protected:
		Transform m_Transform;
	};
}


namespace YAML
{
	template<>
	struct convert<Tomato::Transform> {
		static Node encode(const Tomato::Transform& tran) {
			Node node;
			node["Position"] = tran.Position;
			node["Scale"] = tran.Scale;
			node["Rotation"] = tran.Rotation;
			return node;
		}
		static bool decode(const Node& node, Tomato::Transform& tran) {
			if (!node.IsMap() || node.size() != 3) {
				return false;
			}
			tran.Position = node["Position"].as<Tomato::Float3>();
			tran.Scale = node["Scale"].as<Tomato::Float3>();
			tran.Rotation = node["Rotation"].as<Tomato::Float3>();
			return true;
		}
	};
}