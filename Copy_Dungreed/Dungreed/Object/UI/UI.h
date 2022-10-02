#pragma once
class UI : public Object
{
public:
	enum UI_Type
	{
		NONE,
		HPBAR,
		WEAPON_SLOT,
		INFO,
		MINIMAP,
	};

public:
	UI();

	virtual void Refresh();
	UI_Type GetUIType() { return _uiType; }

protected:
	UI_Type _uiType = NONE;

};

