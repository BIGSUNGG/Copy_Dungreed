#include "framework.h"
#include "LockDoor.h"

LockDoor::LockDoor(int level, int num)
	: Tile(level,num)
{
	_tileType = BLOCK;
	_instance = false;
}

void LockDoor::Update()
{
	if (_open)
	{
		_doorEffectDelayTime += DELTA_TIME;
		while (_doorEffectDelayTime >= _doorEffectDelay)
		{
			_doorEffectDelayTime -= _doorEffectDelayTime;
			for (int i = 0; i < 3; i++)
				DoorOpenEffect();
		}

		if (_collider->IsCollision(GAME->GetPlayer()->GetCollider()))
			MAP_MANAGER->SetCurMap(MAP_MANAGER->GetMapIndex() + _moveDirection);
	}
	else if (_anim->GetCurAnim() == LOCK && _anim->GetIsPlaying() == false)
		_anim->ChangeAnimation(IDLE);
	else if (_anim->GetCurAnim() == IDLE && MAP_MANAGER->GetCurMap()->GetCleared())
		_anim->ChangeAnimation(OPEN);
	else if (_anim->GetCurAnim() == OPEN && _anim->GetIsPlaying() == false)
	{
		_render = false;
		_open = true;
	}

	Tile::Update();
}

void LockDoor::Open()
{
	_render = false;
	_open = true;
}

void LockDoor::DoorOpenEffect()
{
}
