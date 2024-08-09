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
	shared_ptr<UI_Button> _optionButton; // ���� ��ư
	shared_ptr<UI_Button> _gameExitButton; // ���� ���� ��ư

	shared_ptr<UI_Button> _exitButton;
};

