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

	const float _hpBarTextSize = 65.0f;
	const int _hpBarGaugeSize = 294;

};

