#pragma once
class UI_Setting : public UI
{
public:
	UI_Setting();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Quad> _base;
	shared_ptr<Quad> _baseTop;

	shared_ptr<UI_Button> _exitButton;
	shared_ptr<UI_Slider> _slider;
};

