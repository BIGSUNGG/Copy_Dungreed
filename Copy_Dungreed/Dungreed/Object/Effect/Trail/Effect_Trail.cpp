#include "framework.h"
#include "Effect_Trail.h"

Effect_Trail::Effect_Trail(int level, int num)
	: Effect(level,num)
{
	_buffer->_data.selected = 1;
	_buffer->_data.value1 = 1;
	_buffer->_data.value2 = 1;
	_buffer->_data.value3 = 1;
	_buffer->_data.value4 = 1;
}

void Effect_Trail::Update()
{
	_buffer->_data.value4 -= _fadeRatio * DELTA_TIME;

	if (_buffer->_data.value4 <= 0)
	{
		_isActive = false;
		return;
	}
	else
		GetPos() += (_direction * _speed) * DELTA_TIME;

	Object::Update();
}

void Effect_Trail::SetDirection(const Vector2& direction)
{
	_direction = direction;
	_direction.Normalize();
}
