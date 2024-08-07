#include "framework.h"
#include "BackGround.h"

BackGround::BackGround(int level, int num)
	: Object(level, num)
{
	_objectType = Object::Object_Type::BACKGROUND;
	_staticObject = false;
}

void BackGround::Update()
{
	if (GAME->GetPlaying() == true)
	{
		switch (_backGroundType)
		{
		case BackGround::STATIC:
			break;
		case BackGround::WALLPAPER:
			// ī�޶� ��ġ�� ����
			_texture->GetTransform()->GetPos() = CAMERA->GetPos() + CENTER;
			break;
		case BackGround::PERSPECTIVE:
			// ī�޶� �̵��� ���� �̵�
			_texture->GetTransform()->GetPos() += (CAMERA->GetVelocity() * DELTA_TIME) / _perspectiveRatio;
			break;
		default:
			break;
		}
	}

	Object::Update();
}

