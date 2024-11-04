#pragma once
class DashMovementComponent : public MovementComponent
{
public:
	DashMovementComponent(Object* object);

	virtual void Update() override;

	virtual void Dash();
	virtual void DashEnd();

public:
	// Getter Setter
	virtual float GetComponentPriority() override { return 2.f; }
	float& GetCurSpeed() { return _curDashSpeed; }
	bool IsSlowDown() { return _slowDown; }

	virtual void SetDirection(const Vector2& vec);
	virtual void SetMaxSpeed(float speed) { _maxDashSpeed = speed; }
	virtual void SetSlowDownSpeed(float speed) { _slowDownSpeed = speed; }
	virtual void SetKeepMaxSpeedTime(float time) { _keepMaxSpeedTime = time; }
	virtual void SetDashEndEvent(function<void()> func) { _dashEndEvent = func; }
	virtual void SetDashSlowDownEvent(function<void()> func) { _slowDownEvent = func; }
	virtual void SetDashMovementEvent(function<void()> func) { _dashMovementEvent = func; }

protected:
	Vector2 _dashDirection = { 0,0 }; // 대시 방향
	function<void()> _dashMovementEvent;  // 대시 중 매 틱 호출
	function<void()> _slowDownEvent;  // 대시 중 감속할 때 매 틱마다 호출
	function<void()> _dashEndEvent; // 대시가 끝날 때 호출

	bool _dash = false; // 대시 중인지
	bool _slowDown = false; // 대시 중 느려지고 있는지

	float _curDashSpeed = 0.0f; // 대시 현재 속도
	float _maxDashSpeed = 2500.0f; // 대시 최대 속도
	float _slowDownSpeed = 10000.0f; // 대시 속도를 감속하는 속도
	float _dashTime = 0.0f; // 대시를 하고 있는 시간
	float _keepMaxSpeedTime = 0.025f; // 대시 최대 속도를 유지할 수 있는 시간

};

