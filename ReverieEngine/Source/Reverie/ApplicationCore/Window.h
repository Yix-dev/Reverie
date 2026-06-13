#pragma once
#include <functional>
#include <string>
#include <Windows.h>

#include "Reverie/Event/Eventbus.h"

namespace Reverie
{
	class EventBase;

	struct WindowDesc
	{
		std::string Title = "Reverie";
		uint32_t Width;
		uint32_t Height;
	};

	class Window
	{
	public:

		Window() :m_Hwnd(nullptr), m_Width(0), m_Height(0), m_Eventbus(nullptr){}
		~Window();

		Window(const Window& window) = delete;
		Window& operator=(const Window&) = delete;

		void OnUpdate();

		inline uint32_t GetHeight() const { return m_Height; }
		inline uint32_t GetWidth() const { return m_Width; }

		inline HWND GetHandle() const { return m_Hwnd; }

		
		bool IsValid() const { return m_Hwnd != nullptr; }
		void Initialize(const HINSTANCE& instance, const WindowDesc& desc, Eventbus* eventbus);
		void Shutdown();

	private:
		static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_Hwnd;
		Eventbus* m_Eventbus;

		bool m_Maximized = false;
		bool m_Minimized = false;
		bool m_Resizing = false;

		std::string m_Title = "Reverie";
		uint32_t m_Width;
		uint32_t m_Height;

		uint16_t m_Dpi = 96;
		float m_Scale = 1.0f;
	};

}
