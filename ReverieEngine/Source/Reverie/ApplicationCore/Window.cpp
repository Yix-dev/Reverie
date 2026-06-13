#include "pch.h"
#include "Window.h"

#include "Reverie/Event/Event.h"
#include "../Logging/Logger.h"

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

	void Window::Initialize(const HINSTANCE& App, const WindowDesc& Desc, Eventbus* eventbus)
	{
		if (m_Hwnd != nullptr)
			return;
		m_Eventbus = eventbus;

		m_Title = Desc.Title;
		m_Width = Desc.Width;
		m_Height = Desc.Height;

		CORE_INFO("Creating window {0} ({1} {2})", Desc.Title, Desc.Width, Desc.Height);

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
		CORE_ASSERT(success, "Register Class failed");

		RECT R = { 0, 0,  (LONG)m_Width,  (LONG)m_Height };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, FALSE);
		int width = R.right - R.left;
		int height = R.bottom - R.top;
		std::wstring WideTitle(m_Title.begin(), m_Title.end());
		m_Hwnd = CreateWindowExW(0, L"MainWindow", WideTitle.data(),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, App, this);

		m_Dpi = GetDpiForWindow(m_Hwnd);
		m_Scale = (float)m_Dpi / 96.0f;

		CORE_ASSERT(m_Hwnd, "Create Window Failed");

		ShowWindow(m_Hwnd, SW_SHOW);
		UpdateWindow(m_Hwnd);

	}

	Window::~Window()
	{
		Shutdown();
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

	void Window::Shutdown()
	{
		if (m_Hwnd)
		{
			DestroyWindow(m_Hwnd);
			m_Hwnd = nullptr;
		}
	}

	LRESULT Window::WindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
		case WM_ACTIVATE:
		{

			if (LOWORD(wParam) == WA_INACTIVE)
			{
				m_Eventbus->Publish(WindowLostFocusEvent());
			}
			else
			{
				m_Eventbus->Publish(WindowFocusEvent());
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
					m_Eventbus->Publish(AppPauseEvent());
					m_Minimized = true;
					m_Maximized = false;
				}
				else if (wParam == SIZE_MAXIMIZED)
				{
					m_Eventbus->Publish(AppResumeEvent());
					m_Minimized = false;
					m_Maximized = true;
					m_Eventbus->Publish(WindowResizeEvent(m_Width, m_Height));
				}
				else if (wParam == SIZE_RESTORED)
				{

					if (m_Minimized)
					{
						m_Eventbus->Publish(AppResumeEvent());
						m_Minimized = false;
						m_Eventbus->Publish(WindowResizeEvent(m_Width, m_Height));
					}

					else if (m_Maximized)
					{
						m_Eventbus->Publish(AppResumeEvent());
						m_Maximized = false;
						m_Eventbus->Publish(WindowResizeEvent(m_Width, m_Height));
					}
					else if (m_Resizing)
					{
					}
					else
					{
						m_Eventbus->Publish(WindowResizeEvent(m_Width, m_Height));
					}
				}
			}
			return 0;
		}

		case WM_DPICHANGED:
		{
			m_Dpi = HIWORD(wParam);
			m_Scale = (float)m_Dpi / 96.0f;

			RECT* rect = reinterpret_cast<RECT*>(lParam);
			SetWindowPos(m_Hwnd, nullptr,
				rect->left,
				rect->top,
				rect->right - rect->left,
				rect->bottom - rect->top,
				SWP_NOZORDER | SWP_NOACTIVATE
			);

			m_Eventbus->Publish(WindowResizeEvent(m_Width, m_Height));
			return 0;
		}

		case WM_ENTERSIZEMOVE:
		{
			m_Eventbus->Publish(AppPauseEvent());
			m_Resizing = true;
			return 0;
		}

		case WM_EXITSIZEMOVE:
		{
			m_Resizing = false;
			m_Eventbus->Publish(WindowResizeEvent(m_Width, m_Height));
			m_Eventbus->Publish(AppResumeEvent());
			return 0;
		}

		case WM_DESTROY:
		{
			m_Eventbus->Publish(WindowCloseEvent());
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
			m_Eventbus->Publish(MouseScrolledEvent(0.0f, yOffset));
			return 0;
		}

		case WM_MOUSEHWHEEL:
		{
			float xOffset = (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
			m_Eventbus->Publish(MouseScrolledEvent(xOffset, 0.0f));
			return 0;
		}

		case WM_LBUTTONDOWN:
		{
			m_Eventbus->Publish(MouseButtonPressedEvent(VK_LBUTTON));
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			m_Eventbus->Publish(MouseButtonPressedEvent(VK_MBUTTON));
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			m_Eventbus->Publish(MouseButtonPressedEvent(VK_RBUTTON));
			return 0;
		}

		case WM_LBUTTONUP:
		{
			m_Eventbus->Publish(MouseButtonReleasedEvent(VK_LBUTTON));
			return 0;
		}
		case WM_MBUTTONUP:
		{
			m_Eventbus->Publish(MouseButtonReleasedEvent(VK_MBUTTON));
			return 0;
		}
		case WM_RBUTTONUP:
		{
			m_Eventbus->Publish(MouseButtonReleasedEvent(VK_RBUTTON));
			return 0;
		}

		case WM_MOUSEMOVE:
		{
			m_Eventbus->Publish(MouseMovedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			return 0;
		}

		case WM_KEYDOWN:
		{
			bool IsRepeat = (lParam & (1 << 30)) != 0;
			m_Eventbus->Publish(KeyPressedEvent(wParam, IsRepeat ? 1 : 0));
			return 0;
		}

		case WM_KEYUP:
		{
			m_Eventbus->Publish(KeyReleasedEvent(wParam));
			return 0;
		}

		}

		return DefWindowProc(hWnd, Message, wParam, lParam);
	}
}