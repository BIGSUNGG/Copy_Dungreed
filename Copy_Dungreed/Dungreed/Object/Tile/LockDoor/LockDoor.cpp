#include "framework.h"
#include "LockDoor.h"

LockDoor::LockDoor(int level, int num)
	: Tile(level,num)
{
	_tileType = BLOCK;
	_static = false;
}

void LockDoor::Update()
{
	if (GAME->GetPlaying() == true)
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
			{
				function<void()> func = [=]() {
					MAP_MANAGER->SetCurMap(MAP_MANAGER->GetMapIndex() + _moveDirection);
					GAME->SetInput(true);
				};
				XMFLOAT4 color = { 0,0,0,0 };
				bool success = UI_MANAGER->Blink(6,0.15f, color, func);
				if(success) 
					GAME->SetInput(false);
			}
		}
		else if (_anim->GetCurAnim() == LOCK && _anim->GetIsPlaying() == false)
			_anim->ChangeAnimation(IDLE);
		else if (_anim->GetCurAnim() == OPEN && _anim->GetIsPlaying() == false)
			Opened();
	}

	Tile::Update();
}

void LockDoor::SetOwnerMap(shared_ptr<Map> map)
{
	Tile::SetOwnerMap(map);
	map->AddOpenEvent(bind(&LockDoor::Open, this));
	map->AddLockEvent(bind(&LockDoor::Lock, this));
}

void LockDoor::Opened()
{
	_render = false;
	_open = true;
	_anim->ChangeAnimation(OPEN, true);
	_anim->GetIsPlaying() = false;
	_collison = false;
}

void LockDoor::Open()
{
	_render = true;
	_open = false;
	_anim->ChangeAnimation(OPEN);
	_anim->GetIsPlaying() = true;
	_collison = true;
}

void LockDoor::Lock()
{
	_render = true;
	_open = false;
	_anim->ChangeAnimation(LOCK);
	_anim->GetIsPlaying() = true;
	_collison = true;
}


void LockDoor::DoorOpenEffect()
{
}
