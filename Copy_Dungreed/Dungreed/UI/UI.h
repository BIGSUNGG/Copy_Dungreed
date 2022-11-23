#pragma once
class UI
{
public:
	UI();

	virtual void Update();
	virtual void PreRender();
	virtual void Render();

	virtual void Refresh();

};

