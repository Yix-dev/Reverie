#include "pch.h"
#include "Application.h"

#include "Reverie/Event/WindowEvent.h"

namespace Reverie
{
	Application::Application(HINSTANCE instance)
		:m_Instance(instance), m_Eventbus(), m_Window(), m_SystemRegistry()
	{
		WindowDesc desc;
		m_Window.Initialize(instance, {"Reverie", 1920, 1080}, &m_Eventbus);

		m_Eventbus.Subscribe<WindowCloseEvent>([this](WindowCloseEvent& e) {return OnWindowClose(e); }, Priority::Highest);
		//Register Systems

		m_SystemRegistry.InitAll(&m_Eventbus);
	}

	Application::~Application()
	{
		m_SystemRegistry.ShutdownAll();
		m_Window.Shutdown();
	}

	void Application::Run()
	{
		m_Running = true;
		while (m_Running)
		{
			m_Window.OnUpdate();
			m_SystemRegistry.UpdateAll(0);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return true;
	}

}
