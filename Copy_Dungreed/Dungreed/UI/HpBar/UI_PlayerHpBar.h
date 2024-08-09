#pragma once
class UI_PlayerHpBar : public UI
{
public:
	UI_PlayerHpBar();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Object> _hpBarBaseBehind; // 체력바 베이스 텍스쳐
	shared_ptr<Object> _hpBarGauge; // 체력바 게이지 텍스쳐
	shared_ptr<Object> _hpBarBaseForward; // 체력바 게이지 이후 렌더링할 베이스 텍스쳐

	shared_ptr<Object> _dashBarGaugeBaseLeft; // 대시바 왼쪽 베이스 텍스쳐
	shared_ptr<Object> _dashBarGaugeBaseMid; // 대시바 가운데 베이스 텍스쳐
	shared_ptr<Object> _dashBarGaugeBaseRight; // 대시바 오른쪽 베이스 텍스쳐

	shared_ptr<Object> _dashBarGaugeLeft; // 대시바 왼쪽 게이지 텍스쳐
	shared_ptr<Object> _dashBarGaugeMid; // 대시바 가운데 게이지 텍스쳐
 	shared_ptr<Object> _dashBarGaugeRight; // 대시바 오른쪽 게이지 텍스쳐

	shared_ptr<UI_Text> _hpText; // 현재 체력 텍스트
	shared_ptr<UI_Text> _levelText; // 현재 레벨 텍스트

	const int _hpBarGaugeSize = 294; // 체력바 게이지 크기

};

