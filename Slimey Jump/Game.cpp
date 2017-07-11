// File Name	: Game.cpp 
// Description	: Game class implementation
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#include "Game.h"
#include "Indices.h"

#define FPS 60

std::mt19937 RandomNumberGenerator(time(NULL));

Game::Game()
{
	m_StartingTick = 0;
	GameState = State::PLAY;
}

Game::~Game()
{
	delete m_Text;
	m_Text = nullptr;
}

// -------------------
// Author: Rony Hanna
// Description: Function that initializes SDL and glew
// -------------------
int Game::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		std::cout << "ERROR: SDL could not initialize.\n";
		SDL_Quit();
		return -1;
	}

	m_MainWindow = SDL_CreateWindow("Slimey Jump - The Fearless Hobbit 2D Engine (c) Rony Hanna", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	if (m_MainWindow == nullptr)
	{
		std::cout << "ERROR: SDL create window operation failed.\n";
		SDL_Quit();
		return -1;
	}

	SDL_GLContext WindowContext = SDL_GL_CreateContext(m_MainWindow);
	if (WindowContext == nullptr)
	{
		std::cout << "ERROR: Could not create GL Context.\n";
		SDL_Quit();
		return -1;
	}

	if (!(glewExperimental = true))
	{
		std::cout << "ERROR: glew experimental.\n";
		SDL_Quit();
		return -1;
	}

	glewInit();

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	return 0;
}

// -------------------
// Author: Rony Hanna
// Description: A simple game loop function (update -> check for input -> render) 
// -------------------
void Game::GameLoop()
{
	while (GameState != State::EXIT)
	{
		m_StartingTick = SDL_GetTicks();

		UpdateGameComponents();
		ProcessInput();
		Render();
		
		CapFrameRate(m_StartingTick);
	}
}

// -------------------
// Author: Rony Hanna
// Description: Function that handles user input 
// -------------------
void Game::ProcessInput()
{
	SDL_Event _event;

	while (SDL_PollEvent(&_event))
	{
		switch (_event.type)
		{
		case SDL_QUIT:
			GameState = State::EXIT;
			break;

		case SDL_MOUSEMOTION:
			//std::cout << "X: " << _event.motion.x << "\n";
			//std::cout << "Y: " << _event.motion.y << "\n";
			break;

		case SDL_KEYDOWN:
			m_playerVelocity = 0.012;

			if (_event.key.keysym.sym == SDLK_d)
			{
				m_isMovingRight = true;
			}
			else if (_event.key.keysym.sym == SDLK_a)
			{
				m_isMovingLeft = true;
			}
			else if (_event.key.keysym.sym == SDLK_p)
			{
				m_isAudioActive = !m_isAudioActive;
			}

			break;

		case SDL_KEYUP:
			m_isMovingRight = false;
			m_isMovingLeft = false;

			if (_event.key.keysym.sym == SDLK_ESCAPE)
			{
				GameState = State::EXIT;
				break;
			}
			if (_event.key.keysym.sym == SDLK_h)
			{
				m_AlternateScreenMode = !m_AlternateScreenMode;
				if (m_AlternateScreenMode)
				{
					SDL_SetWindowFullscreen(m_MainWindow, SDL_WINDOW_FULLSCREEN);
					SDL_ShowCursor(SDL_DISABLE);
				}
				else
				{
					SDL_SetWindowFullscreen(m_MainWindow, 0);
					SDL_ShowCursor(SDL_ENABLE);
				}
				break;
			}

			// Check if the game is over and if the 'R' key was pressed 
			if (_event.key.keysym.sym == SDLK_r && m_isGameover)
			{
				RestartGame();
				break;
			}
		}
	}
}

// -------------------
// Author: Rony Hanna
// Description: Function that renders out the game components 
// -------------------
void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!m_isGameover)
	{
		RenderBackground();
		RenderPlatforms();
		RenderPlayer();
		m_Text->Render();
	}
	else
		RenderGameOverScene();
	
	SDL_GL_SwapWindow(m_MainWindow);
}

// -------------------
// Author: Rony Hanna
// Description: Function that updates the game components 
// -------------------
void Game::UpdateGameComponents()
{
	if (!m_isGameover)
	{
		dy -= 0.0005f;
		m_PlayerTransformation.GetPos().y += dy;

		// Check if player has fallen 
		if (m_PlayerTransformation.GetPos().y < -0.41f)
		{
			// Game over
			GameState = State::GAME_OVER;
			m_isGameover = true;
		}

		if (m_PlayerTransformation.GetPos().y > 0.2f)
		{
			for (unsigned int i = 0; i < m_NumOfPlatforms; ++i)
			{
				m_PlayerTransformation.GetPos().y = 0.2f;
				m_plat[i].m_y = m_plat[i].m_y - dy;

				if (m_plat[i].m_y < -0.5f)
				{
					m_Score += 55;
					m_plat[i].m_y = 0.48f;
					uniform_real_distribution<float> randomPosX(-0.6f, 0.4f);
					m_plat[i].m_x = randomPosX(RandomNumberGenerator);

					if (m_Score > 3000 && m_Score < 4000)
						m_NumOfPlatforms = 7;
					else if (m_Score > 4000 && m_Score < 6000)
						m_NumOfPlatforms = 6;
					else if (m_Score > 6000 && m_Score < 8000)
						m_NumOfPlatforms = 5;
					else if (m_Score > 8000)
						m_NumOfPlatforms = 4;
				}
			}
		}

		for (unsigned int i = 0; i < m_NumOfPlatforms; ++i)
		{
			if ((m_PlayerTransformation.GetPos().x + 0.2f > m_plat[i].m_x) &&
				(m_PlayerTransformation.GetPos().x < m_plat[i].m_x + 0.2f) &&
				(m_PlayerTransformation.GetPos().y > m_plat[i].m_y + 0.06f) &&
				(m_PlayerTransformation.GetPos().y + 0.06f < m_plat[i].m_y + 0.15f) &&
				(dy < 0))
			{
				if (m_isAudioActive)
					m_AudioManager->playSound(m_JumpSound, 0, false, &m_FmodChannel);

				dy = 0.023f;
				m_plat[i].m_x = 2.0f;
			}
		}

		if (m_isMovingRight)
			m_PlayerTransformation.GetPos().x += m_playerVelocity;

		if (m_isMovingLeft)
			m_PlayerTransformation.GetPos().x -= m_playerVelocity;

		std::string score = "Score " + ToString(m_Score);
		m_Text->SetText(score);
	}
}

// -------------------
// Author: Rony Hanna
// Description: Function that renders the background 
// -------------------
void Game::RenderBackground()
{
	m_SimpleShader.UseProgram();
	m_SimpleShader.UpdateTransform(m_BackgroundTransformation, m_Camera);
	m_texBackground.BindTexture(0);
	m_Background.Draw();
}

// -------------------
// Author: Rony Hanna
// Description: Function that renders the platforms 
// -------------------
void Game::RenderPlatforms()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (unsigned int i = 0; i < m_NumOfPlatforms; ++i)
	{
		
		m_SimpleShader.UpdateTransform(m_PlatformTransformation, m_Camera);
		m_texPlatform.BindTexture(0);
		m_Platform.Draw();

		m_PlatformTransformation.GetPos().x = m_plat[i].m_x;
		m_PlatformTransformation.GetPos().y = m_plat[i].m_y;
	}

	glDisable(GL_BLEND);
}

// -------------------
// Author: Rony Hanna
// Description: Function that renders the player 
// -------------------
void Game::RenderPlayer()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_SimpleShader.UpdateTransform(m_PlayerTransformation, m_Camera);
	m_texPlayer.BindTexture(0);
	m_Player.Draw();
	glDisable(GL_BLEND);
}

// -------------------
// Author: Rony Hanna
// Description: Function that caps the frame rate to a certain game speed 
// -------------------
void Game::CapFrameRate(Uint32 StartingTick)
{
	// Limit the frames per second 
	if ((1000 / FPS > SDL_GetTicks() - StartingTick))
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - StartingTick));
}

// -------------------
// Author: Rony Hanna
// Description: Function that initializes FMOD library 
// -------------------
bool Game::InitFmod()
{
	FMOD_RESULT _result;

	_result = FMOD::System_Create(&m_AudioManager);
	if (_result != FMOD_OK)
		return false;

	_result = m_AudioManager->init(50, FMOD_INIT_NORMAL, 0);

	if (_result != FMOD_OK)
		return false;

	return true;
}

// -------------------
// Author: Rony Hanna
// Description: Function that loads audio 
// -------------------
bool Game::LoadAudio()
{
	FMOD_RESULT _result;
	_result = m_AudioManager->createSound("Assets//Audio//jump.mp3", FMOD_DEFAULT, 0, &m_JumpSound);
	return true;
}

// -------------------
// Author: Rony Hanna
// Description: Function that renders the game over scene 
// -------------------
void Game::RenderGameOverScene()
{
	m_BackgroundTransformation.GetPos().x = -0.85f;
	m_SimpleShader.UseProgram();
	m_SimpleShader.UpdateTransform(m_BackgroundTransformation, m_Camera);
	m_texGameoverScene.BindTexture(0);
	m_Background.Draw();
}

// -------------------
// Author: Rony Hanna
// Description: Function that restarts necessary game components 
// -------------------
void Game::RestartGame()
{
	dy = 0.023f;

	m_NumOfPlatforms = 7;
	m_Score = 0;

	m_PlayerTransformation.GetPos().x = 0.0f;
	m_PlayerTransformation.GetPos().y = -0.30f;

	m_plat[0].m_x = m_PlayerTransformation.GetPos().x;
	m_plat[0].m_y = -0.40f;

	for (unsigned int i = 1; i < m_NumOfPlatforms; ++i)
	{
		uniform_real_distribution<float> randomPosX(-0.6f, 0.5f);
		uniform_real_distribution<float> randomPosY(-0.5f, 0.4f);
		m_plat[i].m_x = randomPosX(RandomNumberGenerator);
		m_plat[i].m_y = randomPosY(RandomNumberGenerator);
	}

	m_isGameover = false;
}

// -------------------
// Author: Rony Hanna
// Description: Starting point function that initializes necessary game components and begins the game loop
// -------------------
void Game::Run()
{
	InitSDL();

	m_SimpleShader.SetProgram(m_SimpleShader.CreateProgram("Assets/Shaders/VertexShader.vs", "Assets/Shaders/FragmentShader.fs"));
	m_texPlayer.InitTexture("Assets//Textures//Slime.png");
	m_texBackground.InitTexture("Assets//Textures//Background.png");
	m_texPlatform.InitTexture("Assets//Textures//grass.png");
	m_texGameoverScene.InitTexture("Assets//Textures//Gameover.png");

	shapes.CreateTexturedQuad();
	m_Player.InitGeometry(shapes.m_TexturedQuad, sizeof(shapes.m_TexturedQuad) / sizeof(shapes.m_TexturedQuad[0]), QuadIndices, sizeof(QuadIndices) / sizeof(QuadIndices[0]));
	m_Background.InitGeometry(shapes.m_TexturedQuad, sizeof(shapes.m_TexturedQuad) / sizeof(shapes.m_TexturedQuad[0]), QuadIndices, sizeof(QuadIndices) / sizeof(QuadIndices[0]));
	m_Platform.InitGeometry(shapes.m_TexturedQuad, sizeof(shapes.m_TexturedQuad) / sizeof(shapes.m_TexturedQuad[0]), QuadIndices, sizeof(QuadIndices) / sizeof(QuadIndices[0]));

	m_PlayerTransformation.GetPos().y = 0.41f;

	m_PlatformTransformation.GetPos().x = 0.0f;
	m_PlatformTransformation.GetScale().x = 1.2f;
	m_PlatformTransformation.GetScale().y = 0.2f;

	m_BackgroundTransformation.GetPos().x = -0.7f;
	m_BackgroundTransformation.GetScale().x = 9.0f;
	m_BackgroundTransformation.GetScale().y = 5.0f;

	m_Camera.initCamera(vec3(0.0f, 0.0f, 1.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 100.0f);

	for (unsigned int i = 0; i < m_NumOfPlatforms; ++i)
	{
		uniform_real_distribution<float> randomPosX(-0.6f, 0.5f);
		uniform_real_distribution<float> randomPosY(-0.5f, 0.4f);
		m_plat[i].m_x = randomPosX(RandomNumberGenerator);
		m_plat[i].m_y = randomPosY(RandomNumberGenerator);
	}

	std::string score = "Score " + ToString(m_Score);

	m_Text = new Text(" ", "Assets//Fonts//Engcomica.ttf");
	m_Text->SetScale(1.0f);
	m_Text->SetPosition(glm::vec2(35.0f, 550.0f));
	m_Text->SetColor(glm::vec3(1.0f, 0.3f, 0.0f));
	m_Text->SetText(score);

	if (!InitFmod() || !LoadAudio())
		std::cout << "WARNING: Unable to load audio files.";

	GameLoop();
}