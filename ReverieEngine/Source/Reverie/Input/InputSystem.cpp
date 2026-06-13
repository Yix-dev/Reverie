#include "pch.h"
#include "InputSystem.h"
#include "Reverie/Logging/Logger.h"
#include "Reverie/Event/Eventbus.h"
#include "Reverie/Event/Event.h"

namespace Reverie::Input
{
	void InputSystem::Initialize(Eventbus* eventbus)
	{
	#define RegisterKey(x) m_KeyName[(x)] = #x
			RegisterKey(LeftMouseButton);
			RegisterKey(RightMouseButton);
			RegisterKey(MiddleMouseButton);
			RegisterKey(Back);
			RegisterKey(Tab);
			RegisterKey(Enter);
			RegisterKey(Shift);
			RegisterKey(Ctrl);
			RegisterKey(Alt);
			RegisterKey(Pause);
			RegisterKey(Capslock);
			RegisterKey(Escape);
			RegisterKey(Space);
			RegisterKey(PageUp);
			RegisterKey(PageDown);
			RegisterKey(End);
			RegisterKey(Home);
			RegisterKey(Left);
			RegisterKey(Up);
			RegisterKey(Right);
			RegisterKey(Down);
			RegisterKey(Select);
			RegisterKey(Printscreen);
			RegisterKey(Execute);
			RegisterKey(Print);
			RegisterKey(Insert);
			RegisterKey(Delete);
			RegisterKey(Help);
			RegisterKey(Num0);
			RegisterKey(Num1);
			RegisterKey(Num2);
			RegisterKey(Num3);
			RegisterKey(Num4);
			RegisterKey(Num5);
			RegisterKey(Num6);
			RegisterKey(Num7);
			RegisterKey(Num8);
			RegisterKey(Num9);
			RegisterKey(A);
			RegisterKey(B);
			RegisterKey(C);
			RegisterKey(D);
			RegisterKey(E);
			RegisterKey(F);
			RegisterKey(G);
			RegisterKey(H);
			RegisterKey(I);
			RegisterKey(J);
			RegisterKey(K);
			RegisterKey(L);
			RegisterKey(M);
			RegisterKey(N);
			RegisterKey(O);
			RegisterKey(P);
			RegisterKey(Q);
			RegisterKey(R);
			RegisterKey(S);
			RegisterKey(T);
			RegisterKey(U);
			RegisterKey(V);
			RegisterKey(W);
			RegisterKey(X);
			RegisterKey(Y);
			RegisterKey(Z);
			RegisterKey(Numpad0);
			RegisterKey(Numpad1);
			RegisterKey(Numpad2);
			RegisterKey(Numpad3);
			RegisterKey(Numpad4);
			RegisterKey(Numpad5);
			RegisterKey(Numpad6);
			RegisterKey(Numpad7);
			RegisterKey(Numpad8);
			RegisterKey(Numpad9);
			RegisterKey(F1);
			RegisterKey(F2);
			RegisterKey(F3);
			RegisterKey(F4);
			RegisterKey(F5);
			RegisterKey(F6);
			RegisterKey(F7);
			RegisterKey(F8);
			RegisterKey(F9);
			RegisterKey(F10);
			RegisterKey(F11);
			RegisterKey(F12);
			RegisterKey(NumLock);
			RegisterKey(ScrollLock);
	 #undef RegisterKey

		eventbus->Subscribe<KeyPressedEvent>([this](KeyPressedEvent& e) { return OnKeyPress(e); }, Priority::Highest);
		eventbus->Subscribe<KeyReleasedEvent>([this](KeyReleasedEvent& e) { return OnKeyRelease(e); }, Priority::Highest);
		eventbus->Subscribe<MouseMovedEvent>([this](MouseMovedEvent& e) { return OnMouseMovement(e); }, Priority::Highest);
		eventbus->Subscribe<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e) { return OnMouseButtonPress(e); }, Priority::Highest);
		eventbus->Subscribe<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& e) { return OnMouseButtonRelease(e); }, Priority::Highest);
		eventbus->Subscribe<MouseScrolledEvent>([this](MouseScrolledEvent& e) { return OnMouseScroll(e); }, Priority::Highest);


	}

	void InputSystem::EndFrame()
	{
		memcpy(m_PreviousKeys, m_CurrentKeys, sizeof(m_CurrentKeys));
		m_LastMouseX = m_MouseX;
		m_LastMouseY = m_MouseY;
		m_ScrollDeltaX = 0;
		m_ScrollDeltaY = 0;
	}

	void InputSystem::OnUpdate()
	{
		
	}

	void InputSystem::Shutdown()
	{
	}

	bool InputSystem::OnKeyPress(KeyPressedEvent& e)
	{
		m_CurrentKeys[e.GetKeyCode()] = true;
		CORE_INFO(m_KeyName[e.GetKeyCode()]);
		return false;
	}

	bool InputSystem::OnKeyRelease(KeyReleasedEvent& e)
	{
		m_CurrentKeys[e.GetKeyCode()] = false;
		return false;
	}

	bool InputSystem::OnMouseScroll(MouseScrolledEvent& e)
	{
		m_ScrollDeltaX += e.GetXOffset();
		m_ScrollDeltaY += e.GetYOffset();
		CORE_INFO("DeltaX: {0}, DeltaY: {1}", e.GetXOffset(), e.GetYOffset());
		return false;
	}

	bool InputSystem::OnMouseButtonPress(MouseButtonPressedEvent& e)
	{
		m_CurrentKeys[e.GetMouseButton()] = true;
		CORE_INFO(m_KeyName[e.GetMouseButton()]);
		return false;
	}

	bool InputSystem::OnMouseButtonRelease(MouseButtonReleasedEvent& e)
	{
		m_CurrentKeys[e.GetMouseButton()] = false;
		return false;
	}

	bool InputSystem::OnMouseMovement(MouseMovedEvent& e)
	{
		m_MouseX = e.GetX();
		m_MouseY = e.GetY();
		return false;
	}

	bool InputSystem::IsKeyDown(InputCode code) const
	{
		return m_CurrentKeys[code];
	}

	bool InputSystem::WasKeyPressed(InputCode code) const
	{
		return m_CurrentKeys[code] && !m_PreviousKeys[code];
	}

	bool InputSystem::WasKeyReleased(InputCode code) const
	{
		return m_PreviousKeys[code] && !m_CurrentKeys[code];
	}

	bool InputSystem::IsKeyHeld(InputCode code) const
	{
		return m_CurrentKeys[code] && m_PreviousKeys[code];
	}
}
