#include"Core.h"


Core::Core():
	m_quit(false),
	m_window(NULL),
	m_renderer(NULL),
	m_counted_frames(0),
	m_is_left_mouse_pressed(false),
	m_is_right_mouse_pressed(false),
	m_max_objects(500), m_steps(4),
	m_solver(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), 10.f, { 0.f, 1000.f }, m_steps)
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

	std::shared_ptr<Entity> e1 = m_solver.AddEntity(Vector2(10, 10), 10, false);
	std::shared_ptr<Entity> e2 = m_solver.AddEntity(Vector2(100, 100), 10, false);
	std::shared_ptr<Entity> e3 = m_solver.AddEntity(Vector2(200, 200), 10, false);
	std::shared_ptr<Entity> e4 = m_solver.AddEntity(Vector2(300, 300), 10, false);

	m_solver.AddSegment(e1, e2, 80);
	m_solver.AddSegment(e2, e3, 80);
	m_solver.AddSegment(e3, e4, 80);
	m_solver.AddSegment(e4, e1, 80);
	m_solver.AddSegment(e1, e3, 80);
	m_solver.AddSegment(e2, e4, 80);
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
			{
				if (m_event.button.button == SDL_BUTTON_LEFT)
				{
					m_is_left_mouse_pressed = true;
				}
				if (m_event.button.button == SDL_BUTTON_RIGHT)
				{
					m_is_right_mouse_pressed = true;
				}
			}
			if (m_event.type == SDL_MOUSEBUTTONUP)
			{
				if (m_event.button.button == SDL_BUTTON_LEFT)
					m_is_left_mouse_pressed = false;
				if (m_event.button.button == SDL_BUTTON_RIGHT)
					m_is_right_mouse_pressed = false;
			}
		}

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

	if (m_is_left_mouse_pressed && m_spawn_timer.GetTicks() >= 100.f)
	{
		m_spawn_timer.Start();
		if (m_max_objects > 0)
		{
			m_max_objects--;
			int x, y;
			SDL_GetMouseState(&x, &y);
			m_solver.AddEntity(Vector2(x, y), 10.f, false);
		}
	}

	if (!m_is_right_mouse_pressed && m_temp_entities.size() > 0)
	{
		for (int i = 1; i < m_temp_entities.size(); i++)
		{
			m_solver.AddConstraint(m_temp_entities[i - 1], m_temp_entities[i], 20.f);
			m_temp_entities[i]->Pinned(false);
		}
		m_temp_entities.clear();
	}

	if (m_is_right_mouse_pressed)
		CreateChain();


	m_solver.Update(1.0 / SCREEN_FPS, m_steps);
}

void Core::Render()
{
	SDL_RenderClear(m_renderer);

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	const std::vector<std::shared_ptr<Entity>>& entities = m_solver.GetEntities();

	for (const std::shared_ptr<Entity>& entity : entities)
	{
		const Vector2& position = entity->GetPosition();

		utils::Draw_Circle(m_renderer, position.x, position.y, entity->GetRadius(), 255, 255, 255, 255);
	}

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	SDL_RenderPresent(m_renderer);
}

void Core::CreateChain()
{
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	Vector2 dv = m_previous_pos - Vector2(mouse_x, mouse_y);

	float dst = sqrt(dv.x * dv.x + dv.y * dv.y);

	if (dst >= 21)
	{
		m_temp_entities.emplace_back(m_solver.AddEntity(Vector2(mouse_x, mouse_y), 10.f, true));
		m_previous_pos = Vector2(mouse_x, mouse_y);
	}
}