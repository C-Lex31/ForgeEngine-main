#pragma once


#include "core/core.h"

namespace Forge {

	class  input
	{
	public:
		static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode) ; }
		static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		static void SetCursosPos() { s_Instance->SetCursorPosImpl(); }
		static void HideCursor() { s_Instance->HideCursorImpl(); }
		static void ShowCursor() { s_Instance->ShowCursorImpl(); }
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int keycode) = 0;
		virtual std::pair<float,float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual void SetCursorPosImpl() = 0;
		virtual void HideCursorImpl() = 0;
		virtual void ShowCursorImpl() = 0;
	private:
		static input* s_Instance;
	};
}
