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
	
	shared_ptr<UI_Text> _displayModeText; // ȭ�� ��� �ؽ�Ʈ
	vector<pair<wstring, int>> _displayMode; // ȭ�� ��� ����Ʈ
	int _displayIndex = 0; // ������ ȭ�� ���

	shared_ptr<UI_Text> _fpsText; // �ִ� FPS �ؽ�Ʈ
	vector<pair<wstring, int>> _fps; // �ִ� FPS ����Ʈ
	int _fpsIndex = 0; // ������ �ִ� FPS
};

