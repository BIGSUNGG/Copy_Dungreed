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
	if (_anim->GetCurAnim() == LOCK && _anim->GetIsPlaying() == false)
		_anim->ChangeAnimation(IDLE);
	else if (_anim->GetCurAnim() == IDLE && MAP_MANAGER->GetCurMap()->GetCleared())
		_anim->ChangeAnimation(OPEN);
	else if (_anim->GetCurAnim() == OPEN && _anim->GetIsPlaying() == false)
		_isActive = false;

	Tile::Update();
}
