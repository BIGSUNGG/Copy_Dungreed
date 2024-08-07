#include "framework.h"
#include "DashMovementComponent.h"

DashMovementComponent::DashMovementComponent(Object* object)
	: MovementComponent(object)
{
	_gravityRatio = 0.f;
	_collision = false;
}

void DashMovementComponent::Update()
{
	// 대시 중이라면
	if (_dash)
	{
		// 현재 남은 대시 속도가 있다면
		if (_curDashSpeed > 0.0f)
		{
			// 대시 속도로 돌진
			GetMoveDir() += (_dashDirection * _curDashSpeed);

			if(_dashMovementEvent != nullptr) 
				_dashMovementEvent();

			// 감속 중이라면 감속
			if (_slowDown)
				_curDashSpeed -= _slowDownSpeed * DELTA_TIME;
			// 감속 중이 아니라면
			else
			{			
				_dashTime += DELTA_TIME;
				if (_dashTime >= _keepMaxSpeedTime)
				{
					_slowDown = true;
					if (_slowDownEvent != nullptr)
						_slowDownEvent();
				}
			}

			MovementComponent::Update();
		}
		// 대시 속도가 없다면
		else
		{
			DashEnd();
		}
	}
}

void DashMovementComponent::Dash()
{
	_dash = true;
	_slowDown = false;
	_dashTime = 0.0f;
	_curDashSpeed = _maxDashSpeed;
}

void DashMovementComponent::DashEnd()
{
	if (!_dash) return;

	_dash = false;

	if (_dashEndEvent != nullptr)
		_dashEndEvent();
}

void DashMovementComponent::SetDirection(const Vector2& vec)
{
	_dashDirection = vec;
	_dashDirection.Normalize();
}
