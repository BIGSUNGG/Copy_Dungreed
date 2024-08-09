#include "framework.h"
#include "UI_Slider.h"

UI_Slider::UI_Slider()
{
}

void UI_Slider::Update()
{
	// 마우스를 땟다면
	if (KEY_UP(VK_LBUTTON)) 
		_hold = false;

	// 누르는 중이라면
	if (_hold)
	{
		// 마우스 위치에 따라 슬라이더 바 위치 변경
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
	// 버튼이 눌리면 hold 활성화
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
