#pragma once
#define BIT(x) (1 << (x))

#define D3D12_GPU_VIRTUAL_ADDRESS_NULL      ((D3D12_GPU_VIRTUAL_ADDRESS)0)
#define D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN   ((D3D12_GPU_VIRTUAL_ADDRESS)-1)

#ifdef REVERIE_ENABLE_ASSERTS
	#include <comdef.h>
	#include "Log.h"
	#define THROW(x) do\
			{                                                                                            \
		        HRESULT hr = (x);                                                                        \
		        if (FAILED(hr)) {                                                                        \
		            _com_error err(hr);                                                                  \
		            CRITICAL("Graphics Error: {0}", #x);                                         \
		            CRITICAL("HRESULT: 0x{0:X}", (uint32_t)hr);                                  \
		            __debugbreak();                                                                      \
		        }                                                                                        \
		    } while (0)
	#define CORE_THROW(x) do\
		{                                                                                            \
	        HRESULT hr = (x);                                                                        \
	        if (FAILED(hr)) {                                                                        \
	            _com_error err(hr);                                                                  \
	            CORE_CRITICAL("Graphics Error: {0}", #x);                                         \
	            CORE_CRITICAL("HRESULT: 0x{0:X}", (uint32_t)hr);                                  \
	            __debugbreak();                                                                      \
	        }                                                                                        \
	    } while (0)
	#define STATIC_ASSERT(x, ...) static_assert(x, __VA_ARGS__)
	#define ASSERT(x, ...) {if(!x) {ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define CORE_ASSERT(x, ...) {if(!x) {CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else 
	#define THROW(x) x
	#define CORE_THROW(x) x
	#define STATIC_ASSERT(x, ...)
	#define ASSERT(x, ...)
	#define CORE_ASSERT(x, ...)
#endif

	