#pragma once
class Map
{
public:
	enum Level
	{
		LEVEL_00,
		LEVEL_01,
		LEVEL_02,
		LEVEL_03,
		LEVEL_04,
		LEVEL_05,
		LEVEL_06,
		LEVEL_07,
		PUBLIC,
	};

	enum Type
	{
		BACKGROUND,
		TILE,
		BUILDING,
		CREATURE,
		EFFECT,
	};

public:
	Map();

	void AddObject(shared_ptr<Object> addObject, Type type);
	void DeleteObject(shared_ptr<Object> addObject, Type type);

	void Update();

	void PreRender();
	void Render();
	void PostRender();
	void ImguiRender();

private:
	vector<vector<shared_ptr<Object>>> _objects;
	shared_ptr<Object> _object = make_shared<Tile>();
};