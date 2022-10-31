#pragma once
class UI
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

	virtual void Update();
	virtual void PreRender();
	virtual void Render();

	virtual void Refresh();
	UI_Type GetUIType() { return _uiType; }

protected:
	UI_Type _uiType = NONE;

};

