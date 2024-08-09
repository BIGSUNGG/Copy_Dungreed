#pragma once
class UI_Info : public UI
{
public:
	UI_Info();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Quad> _goldIcon; // ��� ������ �̹���
	shared_ptr<UI_Text> _goldText; // ��� �ؽ�Ʈ

	shared_ptr<Quad> _hungryIcon; // ��� ������ �̹���
	shared_ptr<Quad> _hungryBase; // ��� ���̽� �̹���
	shared_ptr<Quad> _hungryGauge; // ��� ������ �̹���
	shared_ptr<UI_Text> _hungryText; // ��� �ؽ�Ʈ

};

