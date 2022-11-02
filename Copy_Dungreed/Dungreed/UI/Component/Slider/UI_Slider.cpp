#include "framework.h"
#include "UI_Slider.h"

UI_Slider::UI_Slider()
{
}

void UI_Slider::Update()
{
	if (KEY_UP(VK_LBUTTON))
		_hold = false;

	if (_hold)
	{
		float sizeX = _base->GetTexture()->GetSize().x;
		float mouseX = MOUSE_POS.x - _base->GetTexture()->Left();
		_ratio = mouseX / sizeX;
		if (_ratio < 0)
			_ratio = 0;
		else if (_ratio > 1)
			_ratio = 1;
		_thumb->GetTransform()->GetPos().x = _base->GetTexture()->Left() + ((_base->GetTexture()->Right() - _base->GetTexture()->Left()) * _ratio);
	}

	_base->Update();
	_thumb->Update();
}

void UI_Slider::Render()
{
	_base->Render();
	_thumb->Render();
}

void UI_Slider::SetPos(const Vector2& pos)
{
	_base->SetPos(pos);
	_thumb->GetTransform()->GetPos().y = pos.y;
	_thumb->GetTransform()->GetPos().x = _base->GetTexture()->Left() + ((_base->GetTexture()->Right() - _base->GetTexture()->Left()) * _ratio);
}

void UI_Slider::SetButton(shared_ptr<UI_Button> button)
{
	_base = button;
	function<void()> keyDownfunc = [&]() {
		_hold = true;
	};
	_base->SetKeyDownEvent(keyDownfunc);
}

void UI_Slider::SetRatio(const float& ratio)
{
	_ratio = ratio;
	_thumb->GetTransform()->GetPos().x = _base->GetTexture()->Left() + ((_base->GetTexture()->Right() - _base->GetTexture()->Left()) * _ratio);
}
