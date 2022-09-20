#pragma once
class MapEditor : public GameMode
{
public:
	MapEditor();
	// GameMode을(를) 통해 상속됨
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ImGuiRender() override;

	void AddObject(const bool& toFront);
	void DeleteObject(const bool& toFront);

	void MouseEvenet();
	void InputEvent();
	void ApplyOffset();
	void ApplyChange();
	void ResetOffset();

private:
	shared_ptr<Map> _map;

	Vector2				_mouseOffset;
	Vector2				_mouseAppend;
	Vector2				_curMousePos;
	shared_ptr<Object>	_curObject;

	bool _freeMode	= false;
	bool _autoSave	= true;

	int _objectType		= 2;
	int _objectLevel	= 0;
	int _objectNum		= 10;

	int _mapLevel	= 0;
	int _mapNum		= 0;
};

