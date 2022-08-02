#pragma once
#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

using std::vector;

class GameLevel
{
public:
	vector<GameObject> Bricks;

	GameLevel() {}
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	void Draw(SpriteRenderer& renderer);
	bool IsCompleted();

private:
	void init(vector<vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);

};

#endif