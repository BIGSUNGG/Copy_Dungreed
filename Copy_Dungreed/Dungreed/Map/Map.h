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
	Map(int level, int num, char direction = 0b0000);

	void AddObject(shared_ptr<Object> addObject, int type , bool toFront = false);
	void DeleteObject(Vector2 Pos, int type, bool toFront = false);
	void Reset();

	vector<vector<shared_ptr<Object>>>& GetObjects() { return _objects; }

	Vector2& GetStartPos() { return _startPos; }
	Vector2& GetLeftBottom() { return _leftBottom; }
	Vector2& GetRightTop() { return _rightTop; }

	const int& GetLevel() { return _level; }
	const int& GetNum() { return _num; }
	const int& GetObjectCount() { return _objectCount; }

private:
	vector<vector<shared_ptr<Object>>> _objects;
	int _objectCount = 0;

	Vector2 _startPos;
	Vector2 _leftBottom;
	Vector2 _rightTop;

	int _level;
	int _num;
};