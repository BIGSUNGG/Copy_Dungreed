#include "framework.h"
#include "UI_Setting.h"

UI_Setting::UI_Setting()
	: UI()
{
	// Exit Button
	{
		_exitButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Button/Exit.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Button/Exit_Hover.png");
		quad->SetRight(WIN_WIDTH - 36);
		quad->SetTop(WIN_HEIGHT - 45);
		_exitButton->SetTexture(quad);
		_exitButton->SetHoverTexture(hoverQuad);
		function<void()> func = []() { UI_MANAGER->SetState(UIManager::UI_State::OPTION); };
		_exitButton->SetKeyUpEvent(func);
	}

	// Apply Button
	{
		_applyButton = make_shared<UI_Button>();
		auto quad = make_shared<Quad>(L"Resource/Ui/Setting/Apply.png");
		auto hoverQuad = make_shared<Quad>(L"Resource/Ui/Setting/Apply_Hover.png");
		quad->GetTransform()->GetPos() = Vector2(CENTER.x, 70.f);
		_applyButton->SetTexture(quad);
		_applyButton->SetHoverTexture(hoverQuad);
		function<void()> func = bind(&UI_Setting::ApplySetting, this);
		_applyButton->SetKeyDownEvent(func);
	}
	// Apply Text
	{
		_applyText = make_shared<UI_Text>();
		_applyText->SetPos(Vector2(CENTER.x, 70.f));
		_applyText->SetTextSize(50);
		_applyText->SetTextStatus(UI_Text::Text_Status::MID);
		_applyText->SetText(L"적용");
	}

	// Base
	{
		_base = make_shared<Quad>(L"Resource/Ui/Setting/Setting_Base.png");
		_base->SetBottom(0);
		_base->GetTransform()->GetPos().x = CENTER.x;
		_base->Update();
	}
	// Base Top
	{
		_baseTop = make_shared<Quad>(L"Resource/Ui/Setting/Setting_Top.png");
		_baseTop->SetTop(WIN_HEIGHT);
		_baseTop->GetTransform()->GetPos().x = CENTER.x;
		_baseTop->Update();
	}

	// Volume Slider
	{
		shared_ptr<UI_Text> text = make_shared<UI_Text>();
		text->SetPos({ 275,750 });
		text->SetTextSize(50);
		text->SetText(L"마스터 볼륨");
		_texts.emplace_back(text);
	}
	{
		shared_ptr<UI_Text> text = make_shared<UI_Text>();
		text->SetPos({ 275,650 });
		text->SetTextSize(50);
		text->SetText(L"음악 볼륨");
		_texts.emplace_back(text);
	}
	{
		shared_ptr<UI_Text> text = make_shared<UI_Text>();
		text->SetPos({ 275,550 });
		text->SetTextSize(50);
		text->SetText(L"효과음 볼륨");
		_texts.emplace_back(text);
	}

	// Display
	{
		shared_ptr<UI_Text> text = make_shared<UI_Text>();
		text->SetPos({ 275,350 });
		text->SetTextSize(50);
		text->SetText(L"창모드");
		_texts.emplace_back(text);
	}
	// Fps 
	{
		shared_ptr<UI_Text> text = make_shared<UI_Text>();
		text->SetPos({ 275,250 });
		text->SetTextSize(50);
		text->SetText(L"최대 FPS");
		_texts.emplace_back(text);
	}

	// Sound Slider
	{
		shared_ptr<UI_Slider> slider = make_shared<UI_Slider>();
		shared_ptr<UI_Button> button = make_shared<UI_Button>();
		shared_ptr<Quad> base = make_shared<Quad>(L"Resource/Ui/Slider/Slider_Base.png");
		shared_ptr<Quad> thumb = make_shared<Quad>(L"Resource/Ui/Slider/Slider_Thumb.png");
		button->SetHoverTexture(base);
		button->SetTexture(base);
		slider->SetButton(button);
		slider->SetThumb(thumb);
		slider->SetPos({ 1320,750 });
		slider->SetRatio(SOUND->GetAudioVolume() / 2);
		_sliders.emplace_back(slider);
	}
	{
		shared_ptr<UI_Slider> slider = make_shared<UI_Slider>();
		shared_ptr<UI_Button> button = make_shared<UI_Button>();
		shared_ptr<Quad> base = make_shared<Quad>(L"Resource/Ui/Slider/Slider_Base.png");
		shared_ptr<Quad> thumb = make_shared<Quad>(L"Resource/Ui/Slider/Slider_Thumb.png");
		button->SetHoverTexture(base);
		button->SetTexture(base);
		slider->SetButton(button);
		slider->SetThumb(thumb);
		slider->SetPos({ 1320,650 });
		slider->SetRatio(SOUND->GetBGMVolume() / 2);
		_sliders.emplace_back(slider);
	}
	{
		shared_ptr<UI_Slider> slider = make_shared<UI_Slider>();
		shared_ptr<UI_Button> button = make_shared<UI_Button>();
		shared_ptr<Quad> base = make_shared<Quad>(L"Resource/Ui/Slider/Slider_Base.png");
		shared_ptr<Quad> thumb = make_shared<Quad>(L"Resource/Ui/Slider/Slider_Thumb.png");
		button->SetHoverTexture(base);
		button->SetTexture(base);
		slider->SetButton(button);
		slider->SetThumb(thumb);
		slider->SetPos({ 1320,550 });
		slider->SetRatio(SOUND->GetSFXVolume() / 2);
		_sliders.emplace_back(slider);
	}

	// Display Button
	{
		shared_ptr<UI_Button> button = make_shared<UI_Button>();
		shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Ui/Setting/NextButton_Left.png");
		shared_ptr<Quad> hoverTexture = make_shared<Quad>(L"Resource/Ui/Setting/NextButton_Left_Hover.png");
		button->SetTexture(texture);
		button->SetHoverTexture(hoverTexture);
		button->SetPos(Vector2(800, 350));
		function<void()> func = [&]() {
			--_displayIndex;
			if (_displayIndex < 0)
				_displayIndex = _displayMode.size() - 1;

			_displayModeText->SetText(_displayMode[_displayIndex].first);
		};
		button->SetKeyUpEvent(func);
		_buttons.emplace_back(button);
	}
	{
		shared_ptr<UI_Button> button = make_shared<UI_Button>();
		shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Ui/Setting/NextButton_Right.png");
		shared_ptr<Quad> hoverTexture = make_shared<Quad>(L"Resource/Ui/Setting/NextButton_Right_Hover.png");
		button->SetTexture(texture);
		button->SetHoverTexture(hoverTexture);
		button->SetPos(Vector2(1575, 350));
		function<void()> func = [&]() {
			++_displayIndex;
			if (_displayIndex > _displayMode.size() - 1)
				_displayIndex = 0;

			_displayModeText->SetText(_displayMode[_displayIndex].first);
		};
		button->SetKeyUpEvent(func);
		_buttons.emplace_back(button);
	}

	// Fps Button
	{
		shared_ptr<UI_Button> button = make_shared<UI_Button>();
		shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Ui/Setting/NextButton_Left.png");
		shared_ptr<Quad> hoverTexture = make_shared<Quad>(L"Resource/Ui/Setting/NextButton_Left_Hover.png");
		button->SetTexture(texture);
		button->SetHoverTexture(hoverTexture);
		button->SetPos(Vector2(800, 250));
		function<void()> func = [&]() {
			--_fpsIndex;
			if (_fpsIndex < 0)
				_fpsIndex = 0;

			_fpsText->SetText(_fps[_fpsIndex].first);
		};
		button->SetKeyUpEvent(func);
		_buttons.emplace_back(button);
	}
	{
		shared_ptr<UI_Button> button = make_shared<UI_Button>();
		shared_ptr<Quad> texture = make_shared<Quad>(L"Resource/Ui/Setting/NextButton_Right.png");
		shared_ptr<Quad> hoverTexture = make_shared<Quad>(L"Resource/Ui/Setting/NextButton_Right_Hover.png");
		button->SetTexture(texture);
		button->SetHoverTexture(hoverTexture);
		button->SetPos(Vector2(1575, 250));
		function<void()> func = [&]() {
			++_fpsIndex;
			if (_fpsIndex > _fps.size() - 1)
				_fpsIndex = _fps.size() - 1;

			_fpsText->SetText(_fps[_fpsIndex].first);
		};
		button->SetKeyUpEvent(func);
		_buttons.emplace_back(button);
	}

	// Display Text
	{
		std::pair<wstring, int> _pair = { L"      창화면", 0 };
		_displayMode.push_back(_pair);
		_pair = { L" 테두리 없는 창화면", 1 };
		_displayMode.push_back(_pair);
		_pair = { L"     전체화면", 2 };
		_displayMode.push_back(_pair);
	}

	// Fps Text
	{
		std::pair<wstring, int> _pair = { L"X", 0 };
		_fps.push_back(_pair);
		_pair = { L"30", 30 };
		_fps.push_back(_pair);
		_pair = { L"50", 50 };
		_fps.push_back(_pair);
		_pair = { L"60", 60 };
		_fps.push_back(_pair);
		_pair = { L"80", 80 };
		_fps.push_back(_pair);
		_pair = { L"120", 120 };
		_fps.push_back(_pair);
		_pair = { L"144", 144 };
		_fps.push_back(_pair);
		_pair = { L"160", 160 };
		_fps.push_back(_pair);
		_pair = { L"240", 240 };
		_fps.push_back(_pair);

	}

	// Display
	_displayIndex = GRAPHIC->GetWinMode();
	for (int i = 0; i < _fps.size(); i++)
	{
		if (_fps[i].second == GRAPHIC->GetFpsLimit())
		{
			_fpsIndex = i;
		}
	}

	// Text
	{
		_displayModeText = make_shared<UI_Text>();
		_displayModeText->SetTextStatus(UI_Text::Text_Status::MID);
		_displayModeText->SetTextSize(50);
		_displayModeText->SetPos(Vector2(1070, 350));
		_displayModeText->SetText(_displayMode[_displayIndex].first);
	}
	{
		_fpsText = make_shared<UI_Text>();
		_fpsText->SetTextStatus(UI_Text::Text_Status::MID);
		_fpsText->SetTextSize(60);
		_fpsText->SetPos(Vector2(1187, 250));
		_fpsText->SetText(_fps[_fpsIndex].first);
	}
}

void UI_Setting::Update()
{
	for (auto& slider : _sliders)
		slider->Update();
	for (auto& button : _buttons)
		button->Update();

	_exitButton->Update();
	_applyButton->Update();
}

void UI_Setting::Render()
{
	_base->Render();

	for (auto& text : _texts)
		text->Render();

	for (auto& slider : _sliders)
		slider->Render();

	for (auto& button : _buttons)
		button->Render();

	_applyButton->Render();
	_applyText->Render();
	_displayModeText->Render();
	_fpsText->Render();

	_baseTop->Render();
	_exitButton->Render();
}

void UI_Setting::ApplySetting()
{
	// 소리 설정 저장
	SOUND->SetAudioVolume(_sliders[0]->GetRatio() * 2);
	SOUND->SetBGMVolume(_sliders[1]->GetRatio() * 2);
	SOUND->SetSFXVolume(_sliders[2]->GetRatio() * 2);
	SOUND->SetVolumeAll();
	SOUND->Save();

	// 화면 설정 저장
	GRAPHIC->SetWinMode(_displayMode[_displayIndex].second);
	GRAPHIC->SetFpsLimit(_fps[_fpsIndex].second);
	GRAPHIC->Save();
}