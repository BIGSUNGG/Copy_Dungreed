#pragma once
class Effect_Trail : public Effect
{
public:
	Effect_Trail(int level = 0, int num = 0);

	virtual void Update() override;

public:
	// Getter Setter
	void SetAlpha(const float& alpha) { _buffer->_data.value4 = alpha; }
	void SetFadeRatio(const float& ratio) { _fadeRatio = ratio; }
	void SetSpeed(const float& speed) { _speed = speed; }
	void SetMoveDirection(const Vector2& direction);

protected:
	float _fadeRatio = 1.0f; // 사라지는 속도

	Vector2 _moveDirection = { 0,0 }; // 이동할 방향
	float _speed = 0.0f; // 이동할 속도
};

