#pragma once
class UI_Option : public UI
{
public:
	UI_Option();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Quad> _base;

	shared_ptr<UI_Button> _bookButton;
	shared_ptr<UI_Button> _optionButton; // 설정 버튼
	shared_ptr<UI_Button> _gameExitButton; // 게임 종료 버튼

	shared_ptr<UI_Button> _exitButton;
};

