#include"Core.h"


Core::Core()
	:m_quit(false), m_window(NULL), m_renderer(NULL), m_counted_frames(0), m_is_left_mouse_pressed(false), m_is_right_mouse_pressed(false),
	m_max_objects(500), m_steps(4), m_chain_first_link(true), m_creating_chain(false)
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
	m_body_spawn_timer.Start();

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
					
					//CreateBody();
				}
				if (m_event.button.button == SDL_BUTTON_RIGHT)
				{
					int mouse_x, mouse_y;
					SDL_GetMouseState(&mouse_x, &mouse_y);

					m_previous_pos = Vector2(mouse_x, mouse_y);
					m_is_right_mouse_pressed = true;
				}
			}
			if (m_event.type == SDL_MOUSEBUTTONUP)
			{
				if (m_event.button.button == SDL_BUTTON_LEFT)
					m_is_left_mouse_pressed = false;
				if (m_event.button.button == SDL_BUTTON_RIGHT)
				{
					m_is_right_mouse_pressed = false;
					m_chain_first_link = true;
				}
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

	m_creating_chain = m_is_right_mouse_pressed;


	if (!m_creating_chain && m_temp_chain.m_links.size() > 0)
	{
		for (int i = 1; i < m_temp_chain.m_links.size(); i++)
		{
			m_entities[m_temp_chain.m_links[i].m_index_1].m_pinned = false;
			m_entities[m_temp_chain.m_links[i].m_index_2].m_pinned = false;
		}

		m_chains.emplace_back(m_temp_chain);

		m_temp_chain.m_links.clear();

	}


	//object spawning
	if (m_is_left_mouse_pressed && m_spawn_timer.GetTicks() >= 100.f)
	{
		m_spawn_timer.Start();
		if (m_max_objects > 0)
		{
			m_max_objects--;
			int x, y;
			SDL_GetMouseState(&x, &y);
			m_entities.emplace_back(Vector2(x, y), 10, false);
		}
	}
	
	//chain
	if (m_is_right_mouse_pressed)
	{
		CreateChain();
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (m_body_spawn_timer.GetTicks() >= 500.f && state[SDL_SCANCODE_A])
	{
		m_body_spawn_timer.Start();
		std::cout << "C" << std::endl;
		CreateBody();
	}



	for (int i = 0; i < m_steps; i++)
	{
		Check_Collision();

		for (int j = 0; j < m_entities.size(); j++)
			m_entities[j].Update(1.0 / SCREEN_FPS, m_steps);

		for (int k = 0; k < m_chains.size(); k++)
			m_chains[k].Update(m_entities);

		for (int l = 0; l < m_bodies.size(); l++)
			m_bodies[l].Update(m_entities);
	}


}

void Core::Render()
{
	SDL_RenderClear(m_renderer);

	for (int i = 0; i < m_entities.size(); i++)
		m_entities[i].Render(m_renderer);

	//SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	for (int l = 0; l < m_bodies.size(); l++)
		m_bodies[l].Render(m_renderer, m_entities);

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
				Vector2 u_dv = dv / dst; // unit vector

				float mass_ratio_1 = entity_1.m_radius / (entity_1.m_radius + entity_2.m_radius);
				float mass_ratio_2 = entity_2.m_radius / (entity_1.m_radius + entity_2.m_radius);

				float delta = 0.5f * 0.75f * (dst - collision_dst);

				if(!entity_1.m_pinned)
					entity_1.m_position = entity_1.m_position - u_dv * (mass_ratio_2 * delta);
				if(!entity_2.m_pinned)
					entity_2.m_position = entity_2.m_position + u_dv * (mass_ratio_1 * delta);
			}
		}
	}
}

void Core::CreateChain()
{
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	Vector2 dv = m_previous_pos - Vector2(mouse_x, mouse_y);

	float dst = sqrt(dv.m_x * dv.m_x + dv.m_y * dv.m_y);

	if (dst >= 21)
	{
		if (m_chain_first_link)
		{
			m_chain_first_link = false;
			m_entities.emplace_back(Vector2(mouse_x, mouse_y), 10.f, true);
		}
		else
		{
			m_entities.emplace_back(Vector2(mouse_x, mouse_y), 10.f, true);

			Link temp_link = { m_entities.size() - 2, 
							m_entities.size() - 1 };
			m_temp_chain.m_links.emplace_back(temp_link);
		}

		m_previous_pos = Vector2(mouse_x, mouse_y);
	}
}

void Core::CreateBody()
{
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	m_entities.emplace_back(Vector2(mouse_x - 1, mouse_y - 1), 2.5f, false);
	m_entities.emplace_back(Vector2(mouse_x + 1, mouse_y - 1), 2.5f, false);
	m_entities.emplace_back(Vector2(mouse_x + 1, mouse_y + 1), 2.5f, false);
	m_entities.emplace_back(Vector2(mouse_x - 1, mouse_y + 1), 2.5f, false);

	Stick s_1 = { m_entities.size() - 4 , m_entities.size() - 3, 50.f };
	Stick s_2 = { m_entities.size() - 3 , m_entities.size() - 2, 50.f };
	Stick s_3 = { m_entities.size() - 2 , m_entities.size() - 1, 50.f };
	Stick s_4 = { m_entities.size() - 1 , m_entities.size() - 4, 50.f };
	Stick s_5 = { m_entities.size() - 4 , m_entities.size() - 2, 70.71f };
	Stick s_6 = { m_entities.size() - 3 , m_entities.size() - 1, 70.71f };

	m_temp_body.m_sticks.emplace_back(s_1);
	m_temp_body.m_sticks.emplace_back(s_2);
	m_temp_body.m_sticks.emplace_back(s_3);
	m_temp_body.m_sticks.emplace_back(s_4);
	m_temp_body.m_sticks.emplace_back(s_5);
	m_temp_body.m_sticks.emplace_back(s_6);

	m_bodies.emplace_back(m_temp_body);
	m_temp_body.m_sticks.clear();
}