#pragma once
class UI_PlayerHpBar : public UI
{
public:
	UI_PlayerHpBar();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Object> _hpBarBaseBehind; // ü�¹� ���̽� �ؽ���
	shared_ptr<Object> _hpBarGauge; // ü�¹� ������ �ؽ���
	shared_ptr<Object> _hpBarBaseForward; // ü�¹� ������ ���� �������� ���̽� �ؽ���

	shared_ptr<Object> _dashBarGaugeBaseLeft; // ��ù� ���� ���̽� �ؽ���
	shared_ptr<Object> _dashBarGaugeBaseMid; // ��ù� ��� ���̽� �ؽ���
	shared_ptr<Object> _dashBarGaugeBaseRight; // ��ù� ������ ���̽� �ؽ���

	shared_ptr<Object> _dashBarGaugeLeft; // ��ù� ���� ������ �ؽ���
	shared_ptr<Object> _dashBarGaugeMid; // ��ù� ��� ������ �ؽ���
 	shared_ptr<Object> _dashBarGaugeRight; // ��ù� ������ ������ �ؽ���

	shared_ptr<UI_Text> _hpText; // ���� ü�� �ؽ�Ʈ
	shared_ptr<UI_Text> _levelText; // ���� ���� �ؽ�Ʈ

	const int _hpBarGaugeSize = 294; // ü�¹� ������ ũ��

};

