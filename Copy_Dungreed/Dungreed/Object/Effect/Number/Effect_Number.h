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
	vector<shared_ptr<Quad>> _text; // ���� �ؽ���
	const float _term = 7.5f; // ���� ���� ���� ũ��

	Vector2 _velocity = { 75.f , 300.f }; // �̵��� �ӵ�
	const float _gravity = 400.f; // �߷� ��

	float _runTime = 0.f; // ������Ʈ Ȱ��ȭ �ð�
	const float _alphaStartTime = 0.5f; // ������� �����ϴ� ���� ��ٸ��� �ð�
	const float _alphaSpeed = 2.f; // ���� ������� �ӵ�

};

 