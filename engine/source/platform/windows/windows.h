#pragma once

#include "platform/pi_interface.h"
#include "core/servers/rendering/core_rd/graphics_context.h"
#include"core/drivers/OpenGL/opengl_context.h"
namespace Forge {
	class MsWin : public Window
	{
	public:
		MsWin(const WindowProps& props);
		virtual ~MsWin();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;

		bool IsVSync() const override;
		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		graphics_context* m_context;
		//We basically store all the data here which might be requested by the graphics API and can pass this struct to it as a custom user data without passing the whole class.
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};
}