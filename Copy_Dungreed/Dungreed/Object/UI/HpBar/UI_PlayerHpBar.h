#pragma once
class UI_PlayerHpBar : public UI
{
public:
	UI_PlayerHpBar();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Quad> _hpBarBase;
	shared_ptr<Quad> _hpBarEmpty;
	shared_ptr<Quad> _hpBarGauge;

	const float _hpBarTextSize = 65.0f;
	const int _hpBarGaugeSize = 294;

};

