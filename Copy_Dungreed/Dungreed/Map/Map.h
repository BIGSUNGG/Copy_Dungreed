#pragma once
class Map : public enable_shared_from_this<Map>
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
		LEVEL_00_SPECIAL,
		LEVEL_01_SPECIAL,
		LEVEL_02_SPECIAL,
		LEVEL_03_SPECIAL,
		LEVEL_04_SPECIAL,
		LEVEL_05_SPECIAL,
		LEVEL_06_SPECIAL,
		LEVEL_07_SPECIAL,
		PUBLIC_SPECIAL,
	};

public:
	Map(int level, int num);

	bool CheckCleared();

	void AddObject(shared_ptr<Object> addObject, int type);
	bool DeleteObject(shared_ptr<Object> deleteObject, int type);
	void Paste(shared_ptr<Map> copyMap);
	void Reset();

	void OpenEvent();
	void LockEvent();
	void AddOpenEvent(const function<void()>& func) { _openEvent.emplace_back(func); }
	void AddLockEvent(const function<void()>& func) { _lockEvent.emplace_back(func); }

	vector<vector<shared_ptr<Object>>>& GetObjects() { return _objects; }

	Vector2& GetStartPos()		{ return _mapBasicInfo._startPos; }
	Vector2& GetLeftBottom()	{ return _mapBasicInfo._leftBottom; }
	Vector2& GetRightTop()		{ return _mapBasicInfo._rightTop; }

	bool CanGoTop()		{ return _mapBasicInfo.CanGoTop(); }
	bool CanGoBottom()	{ return _mapBasicInfo.CanGoBottom(); }
	bool CanGoLeft()	{ return _mapBasicInfo.CanGoLeft(); }
	bool CanGoRight()	{ return _mapBasicInfo.CanGoRight(); }

	Vector2& GetTopDoor()		{ return _mapBasicInfo._topDoor; }
	Vector2& GetBottomDoor()	{ return _mapBasicInfo._bottomDoor; }
	Vector2& GetLeftDoor()		{ return _mapBasicInfo._leftDoor; }
	Vector2& GetRightDoor()		{ return _mapBasicInfo._rightDoor; }

	bool GetCleared()		{ return _cleared; }
	const int& GetLevel()		{ return _level; }
	const int& GetNum()			{ return _num; }
	const int& GetObjectCount() { return _mapBasicInfo._objectCount; }

private:
	MapBasic _mapBasicInfo;

	vector<vector<shared_ptr<Object>>> _objects;

	vector<function<void()>> _openEvent;
	vector<function<void()>> _lockEvent;

	int _level;
	int _num;

	bool _cleared = false;
};