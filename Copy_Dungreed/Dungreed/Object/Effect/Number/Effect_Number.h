#pragma once
class Effect_Number : public Effect
{
public:
	Effect_Number();

	virtual void Update() override;
	virtual void Render() override;

public:
	// Getter Setter
	virtual void SetColor(const XMFLOAT4& color);
	virtual void SetPos(const Vector2& pos) override;
	virtual void SetNumber(const int& num);

protected:
	vector<shared_ptr<Quad>> _text; // 문자 텍스쳐
	const float _term = 7.5f; // 문자 사이 공백 크기

	Vector2 _velocity = { 75.f , 300.f }; // 이동할 속도
	const float _gravity = 400.f; // 중력 값

	float _runTime = 0.f; // 오브젝트 활성화 시간
	const float _alphaStartTime = 0.5f; // 사라지기 시작하는 것을 기다리는 시간
	const float _alphaSpeed = 2.f; // 점점 사라지는 속도

};

 