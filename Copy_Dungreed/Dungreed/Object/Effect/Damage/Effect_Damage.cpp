#include "framework.h"
#include "Effect_Damage.h"

Effect_Damage::Effect_Damage()
	: Effect(0,0)
{
}

void Effect_Damage::Update()
{
	_velocity.y -= _gravity * DELTA_TIME;
	_spawnPos += _velocity * DELTA_TIME;
	
	_color.x -= _alphaSpeed * DELTA_TIME;
	_color.y -= _alphaSpeed * DELTA_TIME;
	_color.z -= _alphaSpeed * DELTA_TIME;

	if (_color.x <= 0.5f)
		_isActive = false;
}

void Effect_Damage::Render()
{
	Vector2 pos = _spawnPos - CAMERA->GetPos();

	RECT rect = {
	(long)(pos.x),(long)((WIN_HEIGHT - pos.y) - _size / 1.9f),
	WIN_WIDTH,WIN_HEIGHT
	};

	DirectWrite::GetInstance()->RenderText(_text, rect, _size, _font, _color);
}
