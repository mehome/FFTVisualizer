#include "sdlutil.h"
#include <chrono>


Display::Display(int width, int height)
	: width(width)
	, height(height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Error initializing SDL" << std::endl;
	}
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN); 
	if (window == NULL) 
	{ 
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}

	screenSurface = SDL_GetWindowSurface(window);

	renderer = SDL_CreateRenderer(window, -1, 0);
	
	SDL_UpdateWindowSurface(window);
}

Display::~Display()
{
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Display::drawFFT(float* fftOut, int count)
{
	auto start = std::chrono::high_resolution_clock::now();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0xff, 0, SDL_ALPHA_OPAQUE);

	if (points.size() < count)
	{
		points.resize(count);
	}

	float step = width / (float)count;
	float current = 0.f;
	for (int i = 0; i < count; ++i)
	{
		points[i].x = (int)current;
		points[i].y = (int)height - fftOut[i];
		current += step;
	}

	SDL_RenderDrawLines(renderer, points.data(), count);
	
	SDL_UpdateWindowSurface(window);

	SDL_RenderPresent(renderer);

	SDL_PollEvent(nullptr);
	auto end = std::chrono::high_resolution_clock::now();
	int64_t delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	//std::cout << "Delta: " << delta << std::endl;
}
