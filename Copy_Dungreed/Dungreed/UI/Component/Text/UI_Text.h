#pragma once
class UI_Text : public UI_Component
{
public:
	enum class Text_Status
	{
		LEFT,
		MID,
		RIGHT
	};

public:
	UI_Text();

	virtual void Render() override;

	virtual const Vector2& GetPos() { return _pos; }

	virtual void SetPos(const Vector2& pos);
	virtual void SetText(const wstring& text) { _text = text; }
	virtual void SetTextSize(const float& size) { _size = size; }
	virtual void SetTextFont(const wstring& font) { _font = font; }
	virtual void SetTextColor(const XMFLOAT4& color) { _color = color; }
	virtual void SetTextStatus(const Text_Status& status) { _textStatus = status; }

protected:
	Vector2 _pos;
	wstring _text;
	wstring _font = L"DungGeunMo";
	XMFLOAT4 _color{ 1,1,1,1 };
	Text_Status _textStatus = Text_Status::LEFT;
	float _size = 20.0f;

};

