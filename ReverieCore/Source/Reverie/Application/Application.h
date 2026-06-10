#pragma once
#include "System.h"
#include "Reverie/Event/Event.h"
#include "Reverie/Event/Eventbus.h"
#include "Reverie/Application/Window.h"

namespace Reverie
{
	class WindowCloseEvent;
	class WindowResizeEvent;

	class Application
	{
	public:

		Application(HINSTANCE instance);
		Application(const Application& app) = delete;
		Application& operator=(const Application& app) = delete;
		virtual ~Application();

		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Eventbus m_Eventbus;
		Window m_Window;
		SystemRegistry m_SystemRegistry;
		HINSTANCE m_Instance;
		bool m_Running = false;
	};

	std::unique_ptr<Application> CreateApplication(HINSTANCE Instance);
}
