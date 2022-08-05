#pragma once
class UI
{
	enum UI_Type
	{
		HP_BAR,
		DASH_GAUGE,
		MINI_MAP,
		FOOD,
		GOLD,
	};

	UI();
	virtual ~UI() {}

	virtual void Update();
	virtual void PostRender();

	virtual UI_Type GetType() { return _uiType; }
	virtual vector<shared_ptr<Object>>& GetObjects() { return _objects; }

protected:
	vector<shared_ptr<Object>> _objects;
	UI_Type _uiType = UI_Type::HP_BAR;

};

