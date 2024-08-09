#include "framework.h"
#include "UI_Button.h"

UI_Button::UI_Button()
	: UI_Component()
{
}

void UI_Button::Update()
{
	// ���콺 Ŀ���� ��ư ���� �ִٸ�
	if (_collider->IsCollision(MOUSE_POS))
	{
		_hoverTexture->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();
		_hoverTexture->Update();
		_hover = true;

		// ��ư�� �����ٸ�
		if (KEY_DOWN(VK_LBUTTON))
		{
			_click = true;

			if(_keyDownFunc != nullptr)
				_keyDownFunc();
		}
		// ��ư�� ������ �ִٸ�
		else if (KEY_PRESS(VK_LBUTTON) && _keyPressFunc != nullptr)
			_keyPressFunc();
		// ��ư�� ������ ���ٸ�
		else if (KEY_UP(VK_LBUTTON))
		{
			if(_click==true && _keyUpFunc != nullptr)
				_keyUpFunc();

			_click = false;
		}
	}
	else
	{
		_texture->Update();
		_collider->Update();
		_hover = false;
		_click = false;
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

