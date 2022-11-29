#pragma once


#include "core/input/input.h"

namespace Forge {

	class winInput:public input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual void SetCursorPosImpl() override;
		virtual void HideCursorImpl() override;
		virtual void ShowCursorImpl() override;
	};
}
