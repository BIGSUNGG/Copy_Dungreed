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
	Vector2 _dashDirection = { 0,0 }; // ��� ����
	function<void()> _dashMovementEvent;  // ��� �� �� ƽ ȣ��
	function<void()> _slowDownEvent;  // ��� �� ������ �� �� ƽ���� ȣ��
	function<void()> _dashEndEvent; // ��ð� ���� �� ȣ��

	bool _dash = false; // ��� ������
	bool _slowDown = false; // ��� �� �������� �ִ���

	float _curDashSpeed = 0.0f; // ��� ���� �ӵ�
	float _maxDashSpeed = 2500.0f; // ��� �ִ� �ӵ�
	float _slowDownSpeed = 10000.0f; // ��� �ӵ��� �����ϴ� �ӵ�
	float _dashTime = 0.0f; // ��ø� �ϰ� �ִ� �ð�
	float _keepMaxSpeedTime = 0.025f; // ��� �ִ� �ӵ��� ������ �� �ִ� �ð�

};

