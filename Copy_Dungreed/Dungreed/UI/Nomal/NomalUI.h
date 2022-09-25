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
	const int _hpBarGaugeSize = 294;
	shared_ptr<InstanceQuads> _hpBarGauge;
};

