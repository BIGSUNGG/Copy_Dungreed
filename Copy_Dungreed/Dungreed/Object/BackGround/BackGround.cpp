#include "framework.h"
#include "BackGround.h"

BackGround::BackGround(int level, int num)
	: Object(level, num)
{
	_renderOrder = 1.f;
	_objectType = Object::Object_Type::BACKGROUND;
	_static = false;
}

void BackGround::Update()
{
	if (GAME->GetPlaying() == true)
	{
		switch (_backGroundType)
		{
		case BackGround::STATIC:
			break;
		case BackGround::FOLLOW_CAMERA:
			_texture->GetTransform()->GetPos() = CAMERA->GetPos() + CENTER;
			break;
		case BackGround::FOLLOW_PLAYER:
			_texture->GetTransform()->GetPos() += (CAMERA->GetVelocity() * DELTA_TIME) / _perspectiveRatio;
			break;
		default:
			break;
		}
	}

	Object::Update();
}

