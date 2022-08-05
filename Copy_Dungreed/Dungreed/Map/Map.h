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

public:
	Map(Level level = LEVEL_00, int num = 0, char direction = 0b0000);

	void AddObject(shared_ptr<Object> addObject, Object::Object_Type type);
	void DeleteObject(Vector2 Pos, Object::Object_Type type);

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ImguiRender();

	void Save();
	void Load();
	void Reset();

	vector<vector<shared_ptr<Object>>>& GetObjects() { return _objects; }

	int _objectCount = 0;
private:
	vector<vector<shared_ptr<Object>>> _objects;

	Level _level;
	int _num;
};