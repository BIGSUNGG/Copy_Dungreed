#pragma once
class DashMovementComponent : public MovementComponent
{
public:
	DashMovementComponent(Object* object);

	virtual void Update() override;

	virtual void Dash();
	virtual void DashEnd();

	bool IsSlowDown() { return _slowDown; }
	float& GetCurSpeed() { return _curSpeed; }

	virtual void SetDirection(const Vector2& vec);
	virtual void SetMaxSpeed(float speed) { _speedMax = speed; }
	virtual void SetSlowDownSpeed(float speed) { _slowDownSpeed = speed; }
	virtual void SetKeepMaxSpeedTime(float time) { _keepMaxSpeedTime = time; }
	virtual void SetDashEndEvent(function<void()> func) { _dashEndEvent = func; }
	virtual void SetDashMovementEvent(function<void()> func) { _dashMovementEvent = func; }

protected:
	Vector2 _direction = { 0,0 };
	function<void()> _dashMovementEvent;
	function<void()> _dashEndEvent;

	bool _dash = false;
	bool _slowDown = false;

	float _curSpeed = 0.0f;
	float _runTIme = 0.0f;
	float _slowDownSpeed = 10000.0f;
	float _speedMax = 2500.0f;
	float _keepMaxSpeedTime = 0.025f;

};

