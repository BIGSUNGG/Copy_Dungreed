#pragma once
class UI_HpBar : public UI
{
public:
	UI_HpBar();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Object> _hpBarBase;
	shared_ptr<Object> _hpBarEmpty;
	shared_ptr<Object> _hpBarGauge;

	const float _hpBarTextSize = 50.0f;
	const int _hpBarGaugeSize = 294;

};

