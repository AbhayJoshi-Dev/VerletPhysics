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

	m_entities.push_back(std::make_unique<Ball>(*m_assetManager, Vector(480.f, 270.f)));
	m_entities.push_back(std::make_unique<Ball>(*m_assetManager, Vector(480.f, 200.f)));

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

	CheckBallToBallCollision();
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

void Game::CheckBallToBallCollision()
{
	for (const auto& entity1 : m_entities)
	{
		for (const auto& entity2 : m_entities)
		{
			Ball* b1 = const_cast<Ball*>(dynamic_cast<const Ball*>(entity1.get()));
			Ball* b2 = const_cast<Ball*>(dynamic_cast<const Ball*>(entity2.get()));

			if (IsCollisionBetweenBalls(b1, b2) && entity1 != entity2)
			{
				BallCollision(b1, b2);
			}
		}
	}
}

bool Game::IsCollisionBetweenBalls(Ball* b1, Ball* b2)
{
	double dx = b1->GetPosition().GetX() - b2->GetPosition().GetX();
	double dy = b1->GetPosition().GetY() - b2->GetPosition().GetY();

	double dst = std::sqrt(dx * dx + dy * dy);
	double sumRadi = b1->GetRadius() + b2->GetRadius();

	if (sumRadi < dst)
		return false;

	return true;
}

void Game::BallCollision(Ball* b1, Ball* b2)
{
	Vector normalVector = b1->GetPosition() - b2->GetPosition();
	double dst = std::sqrt(normalVector.GetX() * normalVector.GetX() + normalVector.GetY() * normalVector.GetY());
	if (dst < 0.1)
		dst = 0.1;
	Vector normalVectorNormalized = Vector(normalVector.GetX() / dst, normalVector.GetY() / dst);

	Vector deltaVelocityVector = b1->m_velocity - b2->m_velocity;
	b1->m_velocity.SetX(b1->m_bounce * (b1->m_velocity.GetX() * (b1->m_mass - b2->m_mass) + (2 * b2->m_mass * b2->m_velocity.GetX())) / (b1->m_mass + b2->m_mass));
	b1->m_velocity.SetY(b1->m_bounce * (b1->m_velocity.GetY() * (b1->m_mass - b2->m_mass) + (2 * b2->m_mass * b2->m_velocity.GetY())) / (b1->m_mass + b2->m_mass));
	b2->m_velocity.SetX(-b2->m_bounce * (b2->m_velocity.GetX() * (b2->m_mass - b1->m_mass) + (2 * b1->m_mass * b1->m_velocity.GetX())) / (b1->m_mass + b2->m_mass));
	b2->m_velocity.SetY(-b2->m_bounce * (b2->m_velocity.GetY() * (b2->m_mass - b1->m_mass) + (2 * b1->m_mass * b1->m_velocity.GetY())) / (b1->m_mass + b2->m_mass));
	
	double travelDst = (0.08 + (b1->GetRadius() + b2->GetRadius())) - dst;
	b1->SetPosition(b1->GetPosition() + Vector(0.5 * travelDst * normalVectorNormalized.GetX(), 0.5 * travelDst * normalVectorNormalized.GetY()));
	b2->SetPosition(b2->GetPosition() + Vector(-0.5 * travelDst * normalVectorNormalized.GetX(), -0.5 * travelDst * normalVectorNormalized.GetY()));
}