#pragma once
#include "InputCode.h"
#include "Reverie/System.h"

namespace Reverie
{
	class MouseMovedEvent;
	class MouseButtonReleasedEvent;
	class MouseButtonPressedEvent;
	class MouseScrolledEvent;
	class KeyReleasedEvent;
	class KeyPressedEvent;
}

namespace Reverie::Input
{

	class InputSystem : public System
	{
	public:
		InputSystem() : System() {}
		~InputSystem() override {}

		void Initialize(Eventbus* eventbus) override;
		void OnUpdate() override;
		void Shutdown() override;
		void EndFrame() override;

		bool OnKeyPress(KeyPressedEvent& e);
		bool OnKeyRelease(KeyReleasedEvent& e);
		bool OnMouseScroll(MouseScrolledEvent& e);
		bool OnMouseButtonPress(MouseButtonPressedEvent& e);
		bool OnMouseButtonRelease(MouseButtonReleasedEvent& e);
		bool OnMouseMovement(MouseMovedEvent& e);

		bool IsKeyDown(InputCode code) const;
		bool WasKeyPressed(InputCode code) const;
		bool WasKeyReleased(InputCode code) const;
		bool IsKeyHeld(InputCode code) const;

	private:
		const char* m_KeyName[256];
		bool m_CurrentKeys[256]{};
		bool m_PreviousKeys[256]{};

		float m_MouseX, m_MouseY;
		float m_LastMouseX, m_LastMouseY;
		float m_ScrollDeltaX, m_ScrollDeltaY;
	};
	
}
