#pragma once

namespace Forge {

	class Timestep
	{
	public:
		Timestep(float time=0.0f)
			: m_Time(time)
		{
			
		}
		float GetSec() const { return m_Time; }
		float GetMiliSec() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}