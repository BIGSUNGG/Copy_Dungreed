#include "framework.h"
#include "Player.h"

Player::Player(int level, int num)
	: Creature(level,num)
{
	_creatureType = PLAYER;
}

void Player::Update()
{
	Creature::Update();
}

void Player::InputEvent()
{
	if (KEY_PRESS('W'))
	{
		_texture->GetTransform()->GetPos().x += 
	}
}
