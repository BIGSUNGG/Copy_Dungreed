#pragma once
class MapEditor : public GameMode
{
public:
	MapEditor();
	// GameMode을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ImGuiRender() override;

	virtual void MouseEvenet();
	virtual void ApplyOffset();
	virtual void InputEvent();
	virtual void RefreshChange();
private:
	shared_ptr<Map> _map;

	Vector2 _mouseOffset;
	Vector2 _curMousePos;
	shared_ptr<Object> _curObject;

	bool _isPlaying = true;
	bool _freeMode = false;

	Object::Object_Type _beforeType = Object::Object_Type::TILE;
	int _objectType = 2;

	int _beforeLevel = 0;
	int _beforeNum = 10;

	int _level = 0;
	int _num = 10;
};

