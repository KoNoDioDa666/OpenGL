#pragma once
#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"

using glm::vec2;
using glm::vec3;

class BallObject : public GameObject
{
public:
	float Radius;
	bool Stuck;

	BallObject();
	BallObject(vec2 pos, float radius, vec2 velocity, Texture2D sprite);

	vec2 Move(float dt, unsigned int window_width);
	void Reset(vec2 position, vec2 velocity);
};

#endif