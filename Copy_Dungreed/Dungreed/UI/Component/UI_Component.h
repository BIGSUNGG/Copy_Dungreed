#pragma once
class UI_Component : public UI
{
public:
	UI_Component();

	virtual const Vector2& GetPos() abstract;
	virtual void SetPos(const Vector2& pos) abstract;

};

