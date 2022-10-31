#include "framework.h"
#include "UI_Setting.h"

UI_Setting::UI_Setting()
	: UI()
{
	{
		_exitButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Button/Exit.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Button/Exit_Hover.png");
		quad->SetRight(WIN_WIDTH - 36);
		quad->SetTop(WIN_HEIGHT - 45);
		_exitButton->SetTexture(quad);
		_exitButton->SetHoverTexture(hoverQuad);
		function<void()> func = []() { UI_MANAGER->SetState(UIManager::UI_State::OPTION); };
		_exitButton->SetKeyDownEvent(func);
	}

	{
		_base = make_shared<Quad>(L"Resource/Ui/Setting/Setting_Base.png");
		_base->SetBottom(0);
		_base->GetTransform()->GetPos().x = CENTER.x;
		_base->Update();
	}

	{
		_baseTop = make_shared<Quad>(L"Resource/Ui/Setting/Setting_Top.png");
		_baseTop->SetTop(WIN_HEIGHT);
		_baseTop->GetTransform()->GetPos().x = CENTER.x;
		_baseTop->Update();
	}

	{
		_slider = make_shared<UI_Slider>();
		shared_ptr<UI_Button> baseButton = make_shared<UI_Button>();
		shared_ptr<Quad> sliderTexture = make_shared<Quad>(L"Resource/Ui/Slider/Slider_Base.png");
		baseButton->SetTexture(sliderTexture);
		baseButton->SetHoverTexture(sliderTexture);
		shared_ptr<Quad> thumbTexture = make_shared<Quad>(L"Resource/Ui/Slider/Slider_Thumb.png");
		_slider->SetButton(baseButton);
		_slider->SetThumb(thumbTexture);
		_slider->SetPos(CENTER);
	}
}

void UI_Setting::Update()
{
	_slider->Update();
	_exitButton->Update();
}

void UI_Setting::Render()
{
	_base->Render();
	_slider->Render();

	_baseTop->Render();
	_exitButton->Render();
}
