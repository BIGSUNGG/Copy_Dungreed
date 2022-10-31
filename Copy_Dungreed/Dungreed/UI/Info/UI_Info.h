#pragma once
class UI_Info : public UI
{
public:
	UI_Info();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Quad> _coinIcon;
	shared_ptr<Quad> _hungryIcon;

	shared_ptr<Quad> _hungryGauge;
	shared_ptr<Quad> _hungryGaugeBase;

	const float _infoTextSize = 30.0f;

};

