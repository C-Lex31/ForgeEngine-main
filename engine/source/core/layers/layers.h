#pragma once

#include "core/core.h"
#include "core/events/EventRegister.h"
#include "core/main/timestep.h"

namespace Forge {

	class  Layer
	{
	public:
		Layer(const FString& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnGUIRender() {}
		virtual void OnEvent(Event& event) {}

		const FString& GetName() const { return m_DebugName; }
	protected:
		FString m_DebugName;
	};


}