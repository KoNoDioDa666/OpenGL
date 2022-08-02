#include "animation_component.h"
//#include "Character.h"

AnimComponent::AnimComponent()
	:time(0.0f), Montage(), CurrentAnim(),lastState(Idle),curState(Idle)
{
	Init();
}

//AnimComponent::~AnimComponent()
//{
//
//}

void AnimComponent::Init()
{
	Montage["Idle"] = ResourceManager::GetTexture("paddle");
	Montage["WalkLeft_left"] = ResourceManager::GetTexture("face");
	Montage["WalkLeft_right"] = ResourceManager::GetTexture("block");
	Montage["WalkRight_left"] = ResourceManager::GetTexture("background");
	Montage["WalkRight_right"] = ResourceManager::GetTexture("block_solid");
}

void AnimComponent::Update(float dt)
{
	if (curState == lastState)
	{
		time += dt;
		if (time > 1.0f)
		{
			time -= 1.0f;
		}
	}
	else
	{
		time = 0.0f;
	}

	lastState = curState;
	SelectStateMachine(curState);
}

Texture2D AnimComponent::GetCurrentAnim()
{
	return CurrentAnim;
}

void AnimComponent::SelectStateMachine(AnimState state)
{
	switch (state)
	{
	case Idle:
		HandleIdle();
		break;
	case Jumping:
		HandleJump();
		break;
	case WalkLeft:
		HandleWalkLeft();
		break;
	case WalkRight:
		HandleWalkRight();
		break;
	default:
		HandleIdle();
		break;
	}
}

void AnimComponent::HandleIdle()
{
	CurrentAnim = Montage["Idle"];
}
void AnimComponent::HandleJump()
{

}
void AnimComponent::HandleWalkLeft()
{
	if (time < 0.5f)
	{
		CurrentAnim = Montage["WalkLeft_left"];
	}
	else
	{
		CurrentAnim = Montage["WalkLeft_right"];
	}
}
void AnimComponent::HandleWalkRight()
{
	if (time < 0.5f)
	{
		CurrentAnim = Montage["WalkRight_left"];
	}
	else
	{
		CurrentAnim = Montage["WalkRight_right"];
	}
}