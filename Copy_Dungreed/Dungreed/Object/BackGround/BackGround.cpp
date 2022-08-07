#include "framework.h"
#include "BackGround.h"

BackGround::BackGround(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::BACKGROUND;
}

void BackGround::Update()
{
	switch (_backGroundType)
	{
	case BackGround::STATIC:
		break;
	case BackGround::FOLLOW_CAMERA:	
		_texture->GetTransform()->GetPos() = CAMERA->GetPos() + CENTER;
		break;
	case BackGround::FOLLOW_PLAYER:
		break;
	default:
		break;
	}

	Object::Update();
}

