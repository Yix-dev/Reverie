#include "pch.h"
#include "Reverie/Event/ApplicationEvent.h"
#include "Reverie/Event/KeyEvent.h"
#include "Reverie/Event/MouseEvent.h"
#include "Reverie/Event/WindowEvent.h"

namespace Reverie
{
	LRESULT CALLBACK Window::StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_NCCREATE)
		{
			LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			Window* pObj = reinterpret_cast<Window*>(createStruct->lpCreateParams);

			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pObj));

			return pObj->WindowProc(hWnd, msg, wParam, lParam);
		}

		Window* pObj = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (pObj)
		{
			return pObj->WindowProc(hWnd, msg, wParam, lParam);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	void Window::Initialize(const HINSTANCE& App, const WindowDesc& Desc)
	{
		if (m_Hwnd != nullptr)
			return;
		m_Title = Desc.Title;
		m_Width = Desc.Width;
		m_Height = Desc.Height;

		HZ_CORE_INFO("Creating window {0} ({1} {2})", Desc.Title, Desc.Width, Desc.Height);

		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = StaticWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = App;
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.lpszMenuName = nullptr;
		wc.hIconSm = LoadIcon(App, IDI_APPLICATION);
		wc.lpszClassName = L"MainWindow";
		bool success = RegisterClassEx(&wc);
		HZ_CORE_ASSERT(success, "Register Class failed");

		RECT R = { 0, 0,  (LONG)m_Width,  (LONG)m_Height };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, FALSE);
		int width = R.right - R.left;
		int height = R.bottom - R.top;
		std::wstring WideTitle(m_Title.begin(), m_Title.end());
		m_Hwnd = CreateWindowExW(0, L"MainWindow", WideTitle.data(),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, App, this);

		HZ_CORE_ASSERT(m_Hwnd, "Create Window Failed");

		ShowWindow(m_Hwnd, SW_SHOW);
		UpdateWindow(m_Hwnd);

	}

	Window::~Window()
	{
		ShutDown();
	}

	void Window::OnUpdate()
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Window::ShutDown()
	{
		if (m_Hwnd)
		{
			DestroyWindow(m_Hwnd);
			m_Hwnd = nullptr;
		}
	}

	LRESULT Window::WindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (!m_EventCallback)
			return DefWindowProc(hWnd, Message, wParam, lParam);
		switch (Message)
		{
		case WM_ACTIVATE:
		{

			if (LOWORD(wParam) == WA_INACTIVE)
			{
				WindowLostFocusEvent e;
				m_EventCallback(e);
			}
			else
			{
				WindowFocusEvent e;
				m_EventCallback(e);
			}
			return 0;
		}

		case WM_SIZE:
		{
			m_Width = LOWORD(lParam);
			m_Height = HIWORD(lParam);

			if (true)
			{
				if (wParam == SIZE_MINIMIZED)
				{
					AppPauseEvent e;
					m_EventCallback(e);
					m_Minimized = true;
					m_Maximized = false;
				}
				else if (wParam == SIZE_MAXIMIZED)
				{
					AppResumeEvent e;
					m_EventCallback(e);
					m_Minimized = false;
					m_Maximized = true;
					WindowResizeEvent e1(m_Width, m_Height);
					m_EventCallback(e1);
				}
				else if (wParam == SIZE_RESTORED)
				{

					if (m_Minimized)
					{
						AppResumeEvent e;
						m_EventCallback(e);
						m_Minimized = false;
						WindowResizeEvent e1(m_Width, m_Height);
						m_EventCallback(e1);
					}

					else if (m_Maximized)
					{
						AppResumeEvent e;
						m_EventCallback(e);
						m_Maximized = false;
						WindowResizeEvent e1(m_Width, m_Height);
						m_EventCallback(e1);
					}
					else if (m_Resizing)
					{
					}
					else
					{
						WindowResizeEvent e(m_Width, m_Height);
						m_EventCallback(e);
					}
				}
			}
			return 0;
		}

		case WM_ENTERSIZEMOVE:
		{
			AppPauseEvent e;
			m_EventCallback(e);
			m_Resizing = true;
			return 0;
		}

		case WM_EXITSIZEMOVE:
		{
			m_Resizing = false;
			WindowResizeEvent e1(m_Width, m_Height);
			m_EventCallback(e1);
			AppResumeEvent e;
			m_EventCallback(e);
			return 0;
		}

		case WM_DESTROY:
		{
			WindowCloseEvent e;
			m_EventCallback(e);

			PostQuitMessage(0);
			return 0;
		}

		case WM_MENUCHAR:
		{
			return MAKELRESULT(0, MNC_CLOSE);
		}

		case WM_GETMINMAXINFO:
		{
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
			return 0;
		}
		case WM_MOUSEWHEEL:
		{
			float yOffset = (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
			MouseScrolledEvent e(0.0f, yOffset);
			m_EventCallback(e);
			return 0;
		}

		case WM_MOUSEHWHEEL:
		{
			float xOffset = (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
			MouseScrolledEvent e(xOffset, 0.0f);
			m_EventCallback(e);
			return 0;
		}

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			MouseButtonPressedEvent e(wParam);
			m_EventCallback(e);
			return 0;
		}

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			MouseButtonReleasedEvent e(wParam);
			m_EventCallback(e);
			return 0;
		}

		case WM_MOUSEMOVE:
		{
			MouseMovedEvent e(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			m_EventCallback(e);
			return 0;
		}

		case WM_KEYDOWN:
		{
			bool IsRepeat = (lParam & (1 << 30)) != 0;
			KeyPressedEvent e(wParam, IsRepeat ? 1 : 0);
			m_EventCallback(e);
			return 0;
		}

		case WM_KEYUP:
		{
			KeyReleasedEvent e(wParam);
			m_EventCallback(e);
			return 0;
		}

		}

		return DefWindowProc(hWnd, Message, wParam, lParam);
	}
}