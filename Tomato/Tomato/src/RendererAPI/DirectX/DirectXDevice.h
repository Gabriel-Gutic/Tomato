#pragma once


namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS
	/* Singleton */
	class DirectXDevice
	{
	private:
		DirectXDevice(){}
	public:
		DirectXDevice(const DirectXDevice&) = delete;

		static void Initialize();
		static void Terminate();
		
		static void Clear(const Float4& color);
		static void Swap();
		static void SetRenderTarget(std::any rt);
		static void RefreshRenderTarget(std::any rt, uint32_t width, uint32_t height);

		static std::any GetDevice();
		static std::any GetDeviceContext();
		static std::any GetSwapChain();
		static std::any GetBackBuffer();
	private:
		static void SetViewport(uint32_t width, uint32_t height);
	private:
		static DirectXDevice* s_Instance;
	};
#else
	class DirectXDevice 
	{
	private:
		DirectXDevice() {}
	};
#endif // TOMATO_PLATFORM_WINDOWS
}
