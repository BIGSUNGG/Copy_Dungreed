#include "framework.h"
#include "LockDoor.h"

LockDoor::LockDoor(int level, int num)
	: Tile(level,num)
{
	_tileType = BLOCK;
	_staticObject = false;
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
					MAP_MANAGER->SetCurMap(MAP_MANAGER->GetMapPos() + _moveDirection);
					GAME->SetInput(true);
					GAME->GetPlayer()->SetStatic(false);
				};
				XMFLOAT4 color = { 0,0,0,0 };
				bool success = UI_MANAGER->Blink(6,0.15f, color, func);
				if (success)
				{
					GAME->SetInput(false);
					GAME->GetPlayer()->SetStatic(true);
				}
			}
		}
		else if (_anim->GetCurAnim() == LOCK && _anim->IsPlaying() == false)
			_anim->ChangeAnimation(IDLE);
		else if (_anim->GetCurAnim() == OPEN && _anim->IsPlaying() == false)
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
	_anim->SetIsPlaying(false);
	_collison = false;
}

void LockDoor::Open()
{
	_render = true;
	_open = false;
	_anim->ChangeAnimation(OPEN);
	_anim->SetIsPlaying(true);
	_collison = true;
}

void LockDoor::Lock()
{
	_render = true;
	_open = false;
	_anim->ChangeAnimation(LOCK);
	_anim->SetIsPlaying(true);
	_collison = true;
}


void LockDoor::DoorOpenEffect()
{
	auto trail = make_shared<Effect_Trail>();
	auto quad = make_shared<Quad>(L"Resource/Effect/LockDoor/DoorEffect.png");
	trail->SetTexture(quad);
	trail->GetPos().x = MathUtility::RandomFloat(_texture->GetTransform()->GetPos().x - (_texture->GetHalfSize().x * 0.7), _texture->GetTransform()->GetPos().x + (_texture->GetHalfSize().x * 0.7));
	trail->GetPos().y = MathUtility::RandomFloat(_texture->GetTransform()->GetPos().y - (_texture->GetHalfSize().y * 0.7), _texture->GetTransform()->GetPos().y + (_texture->GetHalfSize().y * 0.7));
	trail->SetAlpha(MathUtility::RandomFloat(0.3f, 0.7f));
	trail->GetObjectTexture()->GetTransform()->GetScale() *= MathUtility::RandomFloat(0.5f, 1.0f);
	trail->SetFadeRatio(0.7f);
	Vector2 effectDirection = _moveDirection * -1;
	trail->SetDirection(effectDirection);
	trail->SetSpeed(100.0f);
	GAME->AddEffect(trail);
}
