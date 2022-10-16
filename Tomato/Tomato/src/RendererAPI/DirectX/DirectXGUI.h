#pragma once
#include "Tomato/GUI/GUI_API.h"


namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS
	class DirectXGUI : public GUI_API
	{
	private:
		virtual void Initialize() override;
		virtual void Terminate() override;
		virtual void Begin() override;
		virtual void End() override;
		
	public:
		static void* GetImTextureID(std::any shaderResourceView);
	};
#else
	class DirectXGUI : public GUI_API
	{
	private:
		virtual void Initialize() override {}
		virtual void Terminate() override {}
		virtual void Begin() override {}
		virtual void End() override {}
	public:
		static void* GetImTextureID(std::any shaderResourceView);
	};
#endif // TOMATO_PLATFORM_WINDOWS
}