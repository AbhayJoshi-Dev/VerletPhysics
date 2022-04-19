#pragma once

#include<SDL.h>

#include"Vector.h"

namespace utils
{
	static float m_currentTime = 0.f;
	static float m_lastTime = 0.f;
	static int m_fps;

	inline float HireTimeInSeconds()
	{
		float t = (float)SDL_GetTicks();
		return t * 0.001f;
	}

	inline void PrintFps()
	{
		m_currentTime = (float)SDL_GetTicks();
		if ((m_currentTime - m_lastTime) >= 1000.f)
		{
			m_lastTime = m_currentTime;
			std::cout << m_fps << std::endl;
			m_fps = 0;
		}
		m_fps++;
	}

	inline float Distance(const Vector& a, const Vector& b)
	{
		float dx = a.GetX() - b.GetX();
		float dy = a.GetY() - b.GetY();

		return std::sqrt(dx * dx + dy * dy);
	}
}