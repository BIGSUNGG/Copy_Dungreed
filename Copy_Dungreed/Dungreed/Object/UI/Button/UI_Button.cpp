#include "framework.h"
#include "UI_Button.h"

UI_Button::UI_Button()
	: UI()
{
}

void UI_Button::Update()
{
	if (_collider->IsCollision(MOUSE_POS))
	{
		_hoverTexture->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();
		_hoverTexture->Update();
		_hover = true;
	}
	else
	{
		Object::Update();
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

void UI_Button::SetHoverTexture(shared_ptr<Quad> texture)
{
	_hoverTexture = texture;
	_hoverTexture->SetPS(L"Shader/ObjectShader/ObjectPixelShader.hlsl");
}
