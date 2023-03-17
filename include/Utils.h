#pragma once

#include<SDL.h>
#include<stdlib.h>

namespace utils
{

	inline float HireTimeInSeconds()
	{
		float t = (float)SDL_GetTicks();
		return t * 0.001f;
	}

	inline int Random(int min, int max)
	{
		return (rand() % (max - min + 1)) + min;
	}

	//https://gist.github.com/derofim/912cfc9161269336f722
	inline int FillCircle(SDL_Renderer* renderer, int x, int y, int radius)
	{
		int offsetx, offsety, d;
		int status;

		offsetx = 0;
		offsety = radius;
		d = radius - 1;
		status = 0;

		while (offsety >= offsetx) {

			status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
				x + offsety, y + offsetx);
			status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
				x + offsetx, y + offsety);
			status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
				x + offsetx, y - offsety);
			status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
				x + offsety, y - offsetx);

			if (status < 0) {
				status = -1;
				break;
			}

			if (d >= 2 * offsetx) {
				d -= 2 * offsetx + 1;
				offsetx += 1;
			}
			else if (d < 2 * (radius - offsety)) {
				d += 2 * offsety - 1;
				offsety -= 1;
			}
			else {
				d += 2 * (offsety - offsetx - 1);
				offsety -= 1;
				offsetx += 1;
			}
		}

		return status;
	}

	//https://gist.github.com/derofim/912cfc9161269336f722
	inline void Set_Pixel(SDL_Renderer* renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderDrawPoint(renderer, x, y);
	}

	//https://gist.github.com/derofim/912cfc9161269336f722
	inline void Draw_Circle(SDL_Renderer* renderer, int p_x, int p_y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		double error = (double)-radius;
		double x = (double)radius - 0.5;
		double y = (double)0.5;
		double cx = p_x - 0.5;
		double cy = p_y - 0.5;

		while (x >= y)
		{
			Set_Pixel(renderer, (int)(cx + x), (int)(cy + y), r, g, b, a);
			Set_Pixel(renderer, (int)(cx + y), (int)(cy + x), r, g, b, a);

			if (x != 0)
			{
				Set_Pixel(renderer, (int)(cx - x), (int)(cy + y), r, g, b, a);
				Set_Pixel(renderer, (int)(cx + y), (int)(cy - x), r, g, b, a);
			}

			if (y != 0)
			{
				Set_Pixel(renderer, (int)(cx + x), (int)(cy - y), r, g, b, a);
				Set_Pixel(renderer, (int)(cx - y), (int)(cy + x), r, g, b, a);
			}

			if (x != 0 && y != 0)
			{
				Set_Pixel(renderer, (int)(cx - x), (int)(cy - y), r, g, b, a);
				Set_Pixel(renderer, (int)(cx - y), (int)(cy - x), r, g, b, a);
			}

			error += y;
			++y;
			error += y;

			if (error >= 0)
			{
				--x;
				error -= x;
				error -= x;
			}
		}
	}
}