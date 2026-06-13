#pragma once
#include "Reverie/System.h"

namespace Reverie::Graphics
{
	using Microsoft::WRL::ComPtr;
	class RenderingSystem : public System
	{
	public:
		RenderingSystem() : System(){}
		~RenderingSystem() override {}

		void Initialize(Eventbus* eventbus) override;
		void OnUpdate() override;
		void Shutdown() override;

	private:
		ComPtr<ID3D12Device> m_Device;
		ComPtr<IDXGIFactory6> m_DxgiFactory;
	};
}


