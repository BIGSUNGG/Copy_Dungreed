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
	virtual void KeyBoradEvenet();

private:
	Vector2 _curMousePos;
	shared_ptr<Object> _curObject;

	Map::Type _objectType = Map::Type::TILE;
	int _curType = 1;
	shared_ptr<Map> _map;

	bool _isPlaying = true;
	bool _freeMode = false;

	int _countObject = 0;

	int _beforeLevel = 0;
	int _beforeType = 0;
	int _beforeNum = 0;

	int _level = 0;
	int _type = 0;
	int _num = 0;

};

