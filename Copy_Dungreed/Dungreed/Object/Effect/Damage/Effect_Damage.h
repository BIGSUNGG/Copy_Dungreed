#pragma once
class Effect_Damage : public Effect
{
public:
	Effect_Damage();

	virtual void Update() override;
	virtual void Render() override;

	virtual void SetPos(const Vector2& pos) override { _spawnPos = pos; }
	virtual void SetDamage(const int& damage) { _text = to_wstring(damage); }

protected:
	wstring _text;
	Vector2 _velocity = { 100.f , 400.f };
	XMFLOAT4 _color{ 1,1,1,1 };
	const wstring _font = L"DungGeunMo";
	const float _alphaSpeed = 0.5f;
	const float _gravity = 800.f;
	const float _size = 60.f;

};

