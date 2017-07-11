// File Name	: Game.h 
// Description	: Sets up game class 
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <random>
#include <cstdlib>
#include <ctime>

#include "Common.h"
#include "Mesh.h"
#include "Shader.h"
#include "Shapes.h"
#include "Texture.h"
#include "MatrixTransformation.h"
#include "Font.h"
#include "Dependencies\FMOD\fmod.hpp"

using std::cout;
using std::uniform_real_distribution;

enum class State { PLAY, GAME_OVER, EXIT, TOTAL_STATES };

struct PlatformPos
{
	float m_x;
	float m_y;
};

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	SDL_Window* m_MainWindow;
	State GameState;

	int InitSDL();

	void GameLoop();
	void ProcessInput();
	void UpdateGameComponents();
	void Render();
	void RenderBackground();
	void RenderPlatforms();
	void RenderPlayer();
	void RenderGameOverScene();
	void RestartGame();

	void CapFrameRate(Uint32);

	bool InitFmod();
	bool LoadAudio();

	Shapes shapes;
	Shader m_SimpleShader;
	Mesh m_Player, m_Background, m_Platform;
	Texture m_texPlayer, m_texBackground, m_texPlatform, m_texGameoverScene;
	Camera m_Camera;
	MatrixTransform m_PlayerTransformation, m_BackgroundTransformation, m_PlatformTransformation;
	PlatformPos m_plat[16];
	Text* m_Text = nullptr;

	FMOD::System* m_AudioManager;
	FMOD::Sound* m_JumpSound;
	FMOD::Channel* m_FmodChannel;

	unsigned short int m_Score;
	unsigned short int m_NumOfPlatforms = 8;
	double m_playerVelocity;
	float dx = 0.0f, dy = 0.0f;

	Uint32 m_StartingTick;

	bool m_isAudioActive = true;
	bool m_isMovingRight = false;
	bool m_isMovingLeft = false;
	bool m_isGameover = false;

	bool m_AlternateScreenMode = false;
};

#endif // !__GAME_H__