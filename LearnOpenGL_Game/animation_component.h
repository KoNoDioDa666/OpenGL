#pragma once
#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <map>
#include <string>

#include "texture.h"
#include "resource_manager.h"

//class Character;

enum AnimState
{
	Idle,
	WalkRight,
	WalkLeft,
	Jumping
};

using std::map;
using std::string;

class AnimComponent
{
public:
	AnimComponent();
	//~AnimComponent();
	void Init();
	void Update(float dt); // delta time
	Texture2D GetCurrentAnim();
	//void setstate(Character* player, AnimState state);

public:
	AnimState lastState, curState;

private:
	void SelectStateMachine(AnimState state);
	void HandleWalkLeft();
	void HandleWalkRight();
	void HandleIdle();
	void HandleJump();

private:
	map<string, Texture2D> Montage;
	float time; // 用于更新的动作状态
	Texture2D CurrentAnim;
};

#endif