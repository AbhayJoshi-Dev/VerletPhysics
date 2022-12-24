#include"Core.h"

Core::Core()
	:m_quit(false), m_window(NULL), m_renderer(NULL)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

	m_window = SDL_CreateWindow("Ball Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (m_window == NULL)
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer = NULL)
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
}

Core::~Core()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void Core::Loop()
{
	while (!m_quit)
	{
		while (SDL_PollEvent(&m_event) != 0)
		{
			if (m_event.type == SDL_QUIT)
				m_quit = true;
		}

		Update();
		Render();

	}
}

void Core::Update()
{

}

void Core::Render()
{

}