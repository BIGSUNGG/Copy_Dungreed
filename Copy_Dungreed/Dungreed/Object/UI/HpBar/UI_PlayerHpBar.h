#pragma once
class UI_PlayerHpBar : public UI
{
public:
	UI_PlayerHpBar();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Object> _hpBarBase;
	shared_ptr<Object> _hpBarEmpty;
	shared_ptr<Object> _hpBarGauge;

	shared_ptr<Object> _dashBarGaugeBaseLeft;
	shared_ptr<Object> _dashBarGaugeBaseMid;
	shared_ptr<Object> _dashBarGaugeBaseRight;

	shared_ptr<Object> _dashBarGaugeLeft;
	shared_ptr<Object> _dashBarGaugeMid;
	shared_ptr<Object> _dashBarGaugeRight;

	const float _hpBarTextSize = 65.0f;
	const int _hpBarGaugeSize = 294;

};

