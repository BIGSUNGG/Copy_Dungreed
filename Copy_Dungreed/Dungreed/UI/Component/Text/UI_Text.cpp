#include "framework.h"
#include "UI_Text.h"

UI_Text::UI_Text()
	: UI_Component()
{
}

void UI_Text::Render()
{
	RECT rect;
	switch (_textStatus)
	{
	case UI_Text::Text_Status::LEFT:
		rect = {
			(long)(_pos.x),(long)((WIN_HEIGHT - _pos.y) - _size / 1.9f),
			WIN_WIDTH,WIN_HEIGHT
		};
		break;
	case UI_Text::Text_Status::MID:
		rect = {
			(long)(_pos.x - (_size * _text.length() / 4)),(long)((WIN_HEIGHT - _pos.y) - _size / 1.9f),
			WIN_WIDTH, WIN_HEIGHT
		};
		break;
	case UI_Text::Text_Status::RIGHT:
		rect = {
			(long)(_pos.x - (_size * _text.length() / 2)),(long)((WIN_HEIGHT - _pos.y) - _size / 1.9f),
			WIN_WIDTH, WIN_HEIGHT
		};
		break;
	default:
		break;
	}
	DirectWrite::GetInstance()->RenderText(_text, rect, _size, _font, _color);
}

void UI_Text::SetPos(const Vector2& pos)
{
	_pos = pos;
}
