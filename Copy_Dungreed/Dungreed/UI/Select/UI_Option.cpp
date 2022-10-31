#include "framework.h"
#include "UI_Option.h"

UI_Option::UI_Option()
	: UI()
{
	_base = make_shared<Quad>(L"Resource/Ui/Option/Option_Base.png");
	_base->GetTransform()->GetPos() = CENTER;
	_base->Update();

	{
		_exitButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Button/Exit.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Button/Exit_Hover.png");
		quad->SetRight(WIN_WIDTH - 36);
		quad->SetTop(WIN_HEIGHT - 45);
		_exitButton->SetTexture(quad);
		_exitButton->SetHoverTexture(hoverQuad);
		function<void()> func = []() { UI_MANAGER->SetState(UIManager::UI_State::NOMAL); };
		_exitButton->SetKeyDownEvent(func);
	}

	{
		_bookButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Option/Book.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Option/Book_Hover.png");
		quad->GetTransform()->GetPos().x = CENTER.x - 155;
		quad->GetTransform()->GetPos().y = CENTER.y;
		_bookButton->SetTexture(quad);
		_bookButton->SetHoverTexture(hoverQuad);
	}

	{
		_optionButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Option/Setting.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Option/Setting_Hover.png");
		quad->GetTransform()->GetPos().x = CENTER.x;
		quad->GetTransform()->GetPos().y = CENTER.y;
		_optionButton->SetTexture(quad);
		_optionButton->SetHoverTexture(hoverQuad);
		function<void()> func = []() { UI_MANAGER->SetState(UIManager::UI_State::SETTING); };
		_optionButton->SetKeyDownEvent(func);
	}

	{
		_gameExitButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Option/Exit.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Option/Exit_Hover.png");
		quad->GetTransform()->GetPos().x = CENTER.x + 155;
		quad->GetTransform()->GetPos().y = CENTER.y;
		_gameExitButton->SetTexture(quad);
		_gameExitButton->SetHoverTexture(hoverQuad);
		function<void()> func = []() { EndProgram(); };
		_gameExitButton->SetKeyDownEvent(func);
	}
}

void UI_Option::Update()
{
	_exitButton->Update();
	_bookButton->Update();
	_optionButton->Update();
	_gameExitButton->Update();
}

void UI_Option::Render()
{
	_base->Render();
	_exitButton->Render();
	_bookButton->Render();
	_optionButton->Render();
	_gameExitButton->Render();
}
