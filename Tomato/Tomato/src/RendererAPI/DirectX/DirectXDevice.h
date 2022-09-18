#pragma once


namespace Tomato
{
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
		static void SetRenderTarget();
		static void RefreshRenderTarget(uint32_t width, uint32_t height);

		static std::any GetDevice();
		static std::any GetDeviceContext();
		static std::any GetSwapChain();
		static std::any GetBackBuffer();
	private:
		static DirectXDevice* s_Instance;
	};
}
