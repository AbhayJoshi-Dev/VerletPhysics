#include<Game.h>

Game::Game()
	:m_assetManager(std::make_unique<AssetManager>())
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;

	int imgFlag = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlag) & imgFlag))
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;

	CreateWindow(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

	m_gameRunning = true;

	m_assetManager->Load(m_renderer, "Ball", "res/gfx/Ball.png");

	m_entities.push_front(std::make_unique<Ball>(*m_assetManager, Vector(1920.f / 4.f, 1080.f / 4.f)));
}

Game::~Game()
{
	IMG_Quit();
	SDL_Quit();
}

void Game::CreateWindow(const char* title, int width, int height)
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer == NULL)
		std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
}

void Game::GameLoop()
{
	while (m_gameRunning)
	{
		m_startTicks = SDL_GetTicks();

		m_newTime = utils::HireTimeInSeconds();
		m_frameTime = m_newTime - m_currentTime;
		m_currentTime = m_newTime;
		m_accumulator += m_frameTime;

		while (m_accumulator >= TIMESTEP)
		{
			while (SDL_PollEvent(&m_event))
			{
				switch (m_event.type)
				{
					case SDL_QUIT:
						m_gameRunning = false;
						break;
					default:
						break;
				}

				for (const auto& entity : m_entities)
					entity->HandleEvents(m_event);
			}
			m_accumulator -= TIMESTEP;
		}
		m_alpha = m_accumulator / TIMESTEP;

		Update();
		Render();

		m_frameTicks = SDL_GetTicks() - m_startTicks;
		if (m_frameTicks < 1000 / 120)
			SDL_Delay(1000 / 120 - m_frameTicks);
	}
	SDL_DestroyWindow(m_window);
}

void Game::Update()
{
	utils::PrintFps();

	for (const auto& entity : m_entities)
		entity->Update();
}

void Game::Render()
{
	SDL_RenderClear(m_renderer);

	for (const auto& entity : m_entities)
	{
		auto drawable = dynamic_cast<const IRenderer *>(entity.get());

		if (drawable)
			drawable->Render(m_renderer);
	}

	SDL_RenderPresent(m_renderer);
}