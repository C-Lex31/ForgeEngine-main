#pragma once

#include <sstream>
#include "core/events/EventRegister.h"
#include "core/core.h"
#include "GLFW/glfw3.h"




namespace Forge {

	struct WindowProps
	{
		FString Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const FString& title = "Forge Engine",
			uint32_t width = 1920,
			uint32_t height = 1080)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	//To be implemented per platform,its just an interface
	class  Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;


		virtual void* GetNativeWindow() const = 0;// It returns a void pointer as it doesnt always have to be a glfw window . In future if I decide to use any other Graphics library..it could return HWIN ..etc

		static FScope<Window>Create(const WindowProps& props = WindowProps());//implemented per platform
	};

	

}