#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "game_object.h"
#include "animation_component.h"

class Character : public GameObject
{
public:
	Character(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
	void Update(float dt);
	void SetState(AnimState state);
private:
	AnimComponent animComponent;
	glm::vec2 lastPosition;
};

#endif