#pragma once


namespace Tomato
{
	class VertexArray
	{
	public:
		VertexArray() = default;
		virtual ~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() {};
	public:
		static std::unique_ptr<VertexArray> CreateUnique(const std::initializer_list<uint8_t>& layout);
		static std::shared_ptr<VertexArray> CreateShared(const std::initializer_list<uint8_t>& layout);
	};
}
