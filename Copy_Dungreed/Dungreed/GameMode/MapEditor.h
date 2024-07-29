#pragma once
class MapEditor : public GameMode
{
public:
	MapEditor();
	MapEditor(int level, int num);

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ImGuiRender() override;

protected:
	void Init(shared_ptr<Map> debugMap);

	void AddObject(bool force = false);
	void DeleteObject();

	void MouseEvenet();
	void InputEvent();
	void ApplyOffset();
	void ApplyChange();
	void ResetOffset();

public:
	shared_ptr<Map> GetCurMap() { return _curMap; }

private:
	shared_ptr<Map> _curMap;
	shared_ptr<Map> _copyMap;

	Vector2				_mouseOffset;
	Vector2				_mouseAppend;
	Vector2				_curMousePos;
	shared_ptr<Object>	_curObject;

	bool _freeMode	= false;
	bool _autoSave	= true;

	int _objectType		= 1;
	int _objectLevel	= 0;
	int _objectNum		= 0;

	int _mapLevel	= 0;
	int _mapNum		= 0;

	const Vector2 _verticalDoorHalfSize = { 60.0f, 198.0f };
	const Vector2 _horizonialDoorHalfSize = { 198.0f, 60.0f };
};

