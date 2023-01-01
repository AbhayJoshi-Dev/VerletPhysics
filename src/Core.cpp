#include"Core.h"


Core::Core()
	:m_quit(false), m_window(NULL), m_renderer(NULL), m_counted_frames(0), m_entity(Vector2(30.f, 30.f), 15.f), m_no_of_objects(10)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

	m_window = SDL_CreateWindow("Ball Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (m_window == NULL)
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer == NULL)
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;

	m_fps_timer.Start();

	m_entities.emplace_back(Vector2(110, 110), 20);
	m_entities.emplace_back(Vector2(20, 110), 15);
	m_entities.emplace_back(Vector2(410, 150), 10);
	m_entities.emplace_back(Vector2(510, 310), 40);

	for (int i = 0; i < m_no_of_objects; i++)
		m_entities.emplace_back(Vector2(0.f, 0.f), 20.f);

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
		m_cap_timer.Start();

		while (SDL_PollEvent(&m_event) != 0)
		{
			if (m_event.type == SDL_QUIT)
				m_quit = true;
		}

		float avgFps = m_counted_frames / (m_fps_timer.GetTicks() / 1000.f);
		if (avgFps > 2000000)
			avgFps = 0.f;

		Update();
		Render();

		++m_counted_frames;

		int frames_ticks = m_cap_timer.GetTicks();
		if (frames_ticks < SCREEN_TICKS_PER_FRAME)
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frames_ticks);

	}
}

void Core::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
		m_entities[i].Update(SCREEN_TICKS_PER_FRAME / 1000.f);
}

void Core::Render()
{
	SDL_RenderClear(m_renderer);

	for (int i = 0; i < m_entities.size(); i++)
		m_entities[i].Render(m_renderer);

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	SDL_RenderPresent(m_renderer);
}
