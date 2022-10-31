#include "framework.h"
#include "UI_Button.h"

UI_Button::UI_Button()
	: UI_Component()
{
}

void UI_Button::Update()
{
	if (_collider->IsCollision(MOUSE_POS))
	{
		_hoverTexture->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();
		_hoverTexture->Update();
		_hover = true;
		if (KEY_DOWN(VK_LBUTTON) && _keyDownFunc != nullptr)
			_keyDownFunc();
		else if (KEY_PRESS(VK_LBUTTON) && _keyPressFunc != nullptr)
			_keyPressFunc();
		else if (KEY_UP(VK_LBUTTON) && _keyUpFunc != nullptr)
			_keyUpFunc();
	}
	else
	{
		_texture->Update();
		_collider->Update();
		_hover = false;
	}
}

void UI_Button::Render()
{
	if (_hover)
		_hoverTexture->Render();
	else
		_texture->Render();
}

void UI_Button::SetPos(const Vector2& pos)
{
	_texture->GetTransform()->GetPos() = pos;
}

void UI_Button::SetTexture(shared_ptr<Quad> texture)
{
	_texture = texture;

	_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	_collider->SetParent(_texture->GetTransform());
}

