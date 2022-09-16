#pragma once


namespace Tomato
{
	class GUI_API
	{
	public:
		virtual void Initialize() = 0;
		virtual void Terminate() = 0;
		virtual void Begin() = 0;
		virtual void End() = 0;
	public:
		static std::unique_ptr<GUI_API> CreateUnique();
		static std::shared_ptr<GUI_API> CreateShared();
	};
}
