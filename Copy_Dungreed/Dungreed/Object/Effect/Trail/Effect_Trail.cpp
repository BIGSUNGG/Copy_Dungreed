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
	// 점점 사라지게
	_buffer->_data.value4 -= _fadeRatio * DELTA_TIME;

	// 완전히 사라졌으면 오브젝트 비활성화
	if (_buffer->_data.value4 <= 0)
	{
		_isActive = false;
		return;
	}
	
	// 이동 방향으로 이동
	GetPos() += (_moveDirection * _speed) * DELTA_TIME;
	Object::Update();
}

void Effect_Trail::SetMoveDirection(const Vector2& direction)
{
	_moveDirection = direction;
	_moveDirection.Normalize();
}
