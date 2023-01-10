#include"Core.h"


Core::Core()
	:m_quit(false), m_window(NULL), m_renderer(NULL), m_counted_frames(0), m_entity(Vector2(30.f, 30.f), 15.f), m_is_mouse_pressed(false),
	m_max_objects(500), m_steps(4)
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
	m_spawn_timer.Start();

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
			if (m_event.type == SDL_MOUSEBUTTONDOWN)
				if (m_event.button.button == SDL_BUTTON_LEFT)
					m_is_mouse_pressed = true;
			if (m_event.type == SDL_MOUSEBUTTONUP)
				if (m_event.button.button == SDL_BUTTON_LEFT)
					m_is_mouse_pressed = false;
		}

		//float avgFps = m_counted_frames / (m_fps_timer.GetTicks() / 1000.f);
		//if (avgFps > 2000000)
			//avgFps = 0.f;

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

	if (m_is_mouse_pressed && m_spawn_timer.GetTicks() >= 100.f)
	{
		m_spawn_timer.Start();
		if (m_max_objects > 1)
		{
			m_max_objects--;
			int x, y;
			SDL_GetMouseState(&x, &y);
			m_entities.emplace_back(Vector2(x, y), utils::Random(5, 18));
		}
	}

	for (int i = 0; i < m_steps; i++)
	{
		Check_Collision();

		for (int i = 0; i < m_entities.size(); i++)
			m_entities[i].Update(1.0 / SCREEN_FPS, m_steps);
	}
}

void Core::Render()
{
	SDL_RenderClear(m_renderer);

	for (int i = 0; i < m_entities.size(); i++)
		m_entities[i].Render(m_renderer);

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	SDL_RenderPresent(m_renderer);
}

void Core::Check_Collision()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		Entity& entity_1 = m_entities[i];

		for (int j = i + 1; j < m_entities.size(); j++)
		{
			Entity& entity_2 = m_entities[j];

			Vector2 dv = entity_1.m_position - entity_2.m_position;
			float dst = sqrt(dv.m_x * dv.m_x + dv.m_y * dv.m_y);
			float collision_dst = entity_1.m_radius + entity_2.m_radius;

			if (dst <= collision_dst)
			{
				Vector2 n = dv / dst;

				float mass_ratio_1 = entity_1.m_radius / (entity_1.m_radius + entity_2.m_radius);
				float mass_ratio_2 = entity_2.m_radius / (entity_1.m_radius + entity_2.m_radius);

				float delta = 0.5f * 0.75f * (dst - collision_dst);

				entity_1.m_position = entity_1.m_position - n * (mass_ratio_2 * delta);
				entity_2.m_position = entity_2.m_position + n * (mass_ratio_1 * delta);
			}
		}
	}
}