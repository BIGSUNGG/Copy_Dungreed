#pragma once
class NomalUI : public UI
{
public:
	NomalUI();
	virtual ~NomalUI();

	virtual void Update() override;
	virtual void PostRender() override;

protected:
	shared_ptr<Object> _hpBarBase;
	shared_ptr<Object> _hpBarEmpty;
	shared_ptr<Object> _hpBarGauge;

	shared_ptr<Object> _weaponSlot1;
	shared_ptr<Object> _weaponSlot2;

	shared_ptr<Object> _goldIcon;
	shared_ptr<Object> _hungryIcon;

	const float _textSize = 50.0f;
	const int _hpBarGaugeSize = 294;
};

