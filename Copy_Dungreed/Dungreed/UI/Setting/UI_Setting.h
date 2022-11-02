#pragma once
class UI_Setting : public UI
{
public:
	UI_Setting();

	virtual void Update() override;
	virtual void Render() override;

protected:
	virtual void ApplySetting();

protected:
	shared_ptr<Quad> _base;
	shared_ptr<Quad> _baseTop;

	shared_ptr<UI_Button> _exitButton;
	shared_ptr<UI_Button> _applyButton;
	shared_ptr<UI_Text> _applyText;

	vector<shared_ptr<UI_Text>> _texts;
	vector<shared_ptr<UI_Slider>> _sliders;
	vector<shared_ptr<UI_Button>> _buttons;
	
	shared_ptr<UI_Text> _screenText;
	vector<pair<wstring, int>> _screen;
	int _screenIndex = 0;

	shared_ptr<UI_Text> _fpsText;
	vector<pair<wstring, int>> _fps;
	int _fpsIndex = 0;
};

