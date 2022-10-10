#include "framework.h"
#include "Effect_Trail.h"

Effect_Trail::Effect_Trail(int level, int num)
	: Effect(level,num)
{
	_buffer->_data.selected = 1;
	_buffer->_data.value1 = 1;
	_buffer->_data.value2 = 1;
	_buffer->_data.value3 = 1;
	_buffer->_data.value4 = 0.5f;
}

void Effect_Trail::Update()
{
	_buffer->_data.value4 -= _fadeRatio * DELTA_TIME;

	if (_buffer->_data.value4 <= 0)
		_isActive = false;

	Object::Update();
}
