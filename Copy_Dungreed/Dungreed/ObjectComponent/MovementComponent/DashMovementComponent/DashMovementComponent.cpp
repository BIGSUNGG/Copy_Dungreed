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
	// ��� ���̶��
	if (_dash)
	{
		// ���� ���� ��� �ӵ��� �ִٸ�
		if (_curDashSpeed > 0.0f)
		{
			// ��� �ӵ��� ����
			GetMoveDir() += (_dashDirection * _curDashSpeed);

			if(_dashMovementEvent != nullptr) 
				_dashMovementEvent();

			// ���� ���̶�� ����
			if (_slowDown)
				_curDashSpeed -= _slowDownSpeed * DELTA_TIME;
			// ���� ���� �ƴ϶��
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
		// ��� �ӵ��� ���ٸ�
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
