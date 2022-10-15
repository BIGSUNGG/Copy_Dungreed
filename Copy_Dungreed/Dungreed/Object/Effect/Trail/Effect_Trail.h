#pragma once
class Effect_Trail : public Effect
{
public:
	Effect_Trail(int level = 0, int num = 0);

	virtual void Update() override;

	void SetAlpha(const float& alpha) { _buffer->_data.value4 = alpha; }
	void SetFadeRatio(const float& ratio) { _fadeRatio = ratio; }
	void SetSpeed(const float& speed) { _speed = speed; }
	void SetDirection(const Vector2& direction) { _direction = direction; }

protected:
	float _fadeRatio = 1.0f;

	Vector2 _direction = { 0,0 };
	float _speed = 0.0f;
};

