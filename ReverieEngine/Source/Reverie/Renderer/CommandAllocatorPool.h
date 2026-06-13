#pragma once

namespace Reverie::Graphics
{
	class CommandAllocatorPool
	{
	public:
		CommandAllocatorPool(D3D12_COMMAND_LIST_TYPE type);
		~CommandAllocatorPool();

		void Create(ID3D12Device* device);
		void Shutdown();

		ID3D12CommandAllocator* RequestAllocator(uint64_t completedFenceValue);
		void DiscardAllocator(uint64_t fenceValue, ID3D12CommandAllocator* allocator);

		

	private:

	};
}