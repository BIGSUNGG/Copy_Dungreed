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

	void AddObject(shared_ptr<Object> addObject, int type , bool toFront = false);
	void DeleteObject(Vector2 Pos, Object::Object_Type type, bool toFront = false);

	void Save();
	void Load();
	void Reset();

	Vector2& GetStartPos() { return _startPos; }
	Vector2& GetLeftBottom() { return _leftBottom; }
	Vector2& GetRightTop() { return _rightTop; }

	int _objectCount = 0;
private:

	Vector2 _startPos;
	Vector2 _leftBottom;
	Vector2 _rightTop;

	Level _level;
	int _num;
};