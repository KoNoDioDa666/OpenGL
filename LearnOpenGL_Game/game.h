#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
//const float PLAYER_VELOCITY(500.0f);
const float PLAYER_VELOCITY(100.0f);
//const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(20.0f, -70.0f);
const float BALL_RADIUS = 12.5f;

class Game
{
public:
	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;
	std::vector<GameLevel> Levels;
	unsigned int Level;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	void DoCollisions();

	void ResetLevel();
	void ResetPlayer();
};

#endif