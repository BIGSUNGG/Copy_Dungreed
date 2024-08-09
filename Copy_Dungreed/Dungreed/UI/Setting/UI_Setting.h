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
	
	shared_ptr<UI_Text> _displayModeText; // 화면 모드 텍스트
	vector<pair<wstring, int>> _displayMode; // 화면 모드 리스트
	int _displayIndex = 0; // 선택한 화면 모드

	shared_ptr<UI_Text> _fpsText; // 최대 FPS 텍스트
	vector<pair<wstring, int>> _fps; // 최대 FPS 리스트
	int _fpsIndex = 0; // 선택한 최대 FPS
};

