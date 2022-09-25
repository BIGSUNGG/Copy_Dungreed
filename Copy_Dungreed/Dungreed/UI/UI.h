#pragma once
class UI
{
public:
	enum UI_Type
	{
		NOMAL,
	};

	UI();
	virtual ~UI() {}

	virtual void Update() abstract;
	virtual void PostRender() abstract;

	virtual UI_Type GetType() { return _uiType; }

protected:
	UI_Type _uiType = UI_Type::NOMAL;

};

