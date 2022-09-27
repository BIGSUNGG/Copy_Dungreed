#pragma once
class NomalUI : public UI
{
public:
	NomalUI();
	virtual ~NomalUI();

	virtual void Update() override;
	virtual void SetRTV() override;
	virtual void PostRender() override;

protected:
	shared_ptr<Quad> _cursur;

	shared_ptr<Object> _hpBarBase;
	shared_ptr<Object> _hpBarEmpty;
	shared_ptr<Object> _hpBarGauge;

	shared_ptr<Object> _weaponSlot1;
	shared_ptr<Object> _weaponSlot2;

	shared_ptr<Object> _coinIcon;
	shared_ptr<Object> _hungryIcon;	

	const float _hpBarTextSize = 50.0f;
	const float _infoTextSize = 30.0f;
	const int _hpBarGaugeSize = 294;
};

