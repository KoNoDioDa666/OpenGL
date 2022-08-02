#include "Character.h"

Character::Character(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos, size, sprite), lastPosition(this->Position) {}

void Character::Update(float dt)
{
	// ��ֹͣ�ƶ��������Idle״̬
	if (this->Position == lastPosition)
	{
		SetState(Idle);
	}
	lastPosition = this->Position;

	animComponent.Update(dt);

	this->Sprite = animComponent.GetCurrentAnim();
}

void Character::SetState(AnimState state)
{
	animComponent.curState = state;
}