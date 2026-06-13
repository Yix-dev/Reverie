#include "pch.h"
#include "Application.h"


#include "../Logging/Logger.h"
#include "Reverie/Event/WindowEvent.h"
#include "Reverie/Log.h"
#include "Reverie/Audio/AudioSystem.h"
#include "Reverie/Input/InputSystem.h"
#include "Reverie/Renderer/RenderingSystem.h"

namespace Reverie
{
	Application::Application(HINSTANCE instance)
		:m_Instance(instance), m_Eventbus(), m_Window(), m_SystemRegistry()
	{
		Logger::Initialize(&m_Eventbus);

		m_Window.Initialize(instance, {"Reverie", 1280, 720}, &m_Eventbus);

		m_Eventbus.Subscribe<WindowCloseEvent>([this](WindowCloseEvent& e) {return OnWindowClose(e); }, Priority::Highest);
		//Register Systems
		m_SystemRegistry.Register<Input::InputSystem>();
		m_SystemRegistry.Register<Graphics::RenderingSystem>();
		m_SystemRegistry.Register<Audio::AudioSystem>();
		

		m_SystemRegistry.InitAll(&m_Eventbus);
		CORE_INFO("Welcome");
		
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

			m_SystemRegistry.EndFrameAll();
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
