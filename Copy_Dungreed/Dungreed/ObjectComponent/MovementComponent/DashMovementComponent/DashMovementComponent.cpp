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
	if (_dash)
	{
		if (_curSpeed > 0.0f)
		{
			GetMovement() += (_direction * _curSpeed);

			if(_dashMovementEvent != nullptr) 
				_dashMovementEvent();

			if (_slowDown)
				_curSpeed -= _slowDownSpeed * DELTA_TIME;
			else
			{
				_runTIme += DELTA_TIME;

				if (_runTIme >= _keepMaxSpeedTime)
				{
					_slowDown = true;
					if (_slowDownEvent != nullptr)
						_slowDownEvent();
				}
			}
			MovementComponent::Update();
		}
		else if (_dashEndEvent != nullptr) 
			_dashEndEvent();
	}
}

void DashMovementComponent::Dash()
{
	_dash = true;
	_slowDown = false;
	_runTIme = 0.0f;
	_curSpeed = _speedMax;
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
	_direction = vec;
	_direction.Normalize();
}
