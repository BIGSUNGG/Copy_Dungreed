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
	wstring _text; // 텍스트
	wstring _font = L"DungGeunMo"; // 텍스트 폰트
	Vector2 _pos; // 텍스트 위치
	XMFLOAT4 _color{ 1,1,1,1 }; // 텍스츠 색
	Text_Status _textStatus = Text_Status::LEFT; // 텍스트 위치
	float _size = 20.0f; // 텍스트 사이즈

};

