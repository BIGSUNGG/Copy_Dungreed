#pragma once
class UI_Info : public UI
{
public:
	UI_Info();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Object> _coinIcon;
	shared_ptr<Object> _hungryIcon;

	const float _infoTextSize = 30.0f;

};

