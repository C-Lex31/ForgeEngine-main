#include "frpch.h"
#include "pi_interface.h"

#ifdef FR_PLATFORM_WINDOWS
#include "windows/windows.h"
#endif

namespace Forge
{
	FScope<Window> Window::Create(const WindowProps& props)
	{
#ifdef FR_PLATFORM_WINDOWS
		return std::make_unique<MsWin>(props);
#else
		FR_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}