#pragma once
class Effect_Number : public Effect
{
public:
	Effect_Number();

	virtual void Update() override;
	virtual void Render() override;

	virtual void SetColor(const XMFLOAT4& color);
	virtual void SetPos(const Vector2& pos) override;
	virtual void SetNumber(const int& num);

protected:
	vector<shared_ptr<Quad>> _text;
	Vector2 _velocity = { 75.f , 300.f };
	float _runTime = 0.f;
	const float _term = 7.5f;
	const float _alphaStartTime = 0.5f;
	const float _alphaSpeed = 2.f;
	const float _gravity = 400.f;

};

 