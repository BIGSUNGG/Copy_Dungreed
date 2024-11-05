#pragma once
class StageMap : public enable_shared_from_this<StageMap>
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
	StageMap(int level, int num);

	// 모든 몬스터가 처치되었는지
	bool CheckClear();

public:
	// 오브젝트
	void AddObject(shared_ptr<Object> addObject, int type);
	bool DeleteObject(shared_ptr<Object> deleteObject);
	bool DeleteObject(shared_ptr<Object> deleteObject, int type);

	// 맵	
	// 이 객체에 copyMap을 복사
	void Paste(shared_ptr<StageMap> copyMap);
	// 맵 초기화
	void Reset();

	// Open Lock
	void OpenEvent();
	void LockEvent();
	void AddOpenEvent(const function<void()>& func) { _openEvent.emplace_back(func); }
	void AddLockEvent(const function<void()>& func) { _lockEvent.emplace_back(func); }

public:
	// Getter Setter
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

	bool GetCleared()		{ return _clear; }
	const int& GetLevel()		{ return _mapBasicInfo._level; }
	const int& GetNum()			{ return _mapBasicInfo._num; }
	const int& GetObjectCount() { return _mapBasicInfo._objectCount; }

private:
	StageMapBasic _mapBasicInfo; // 맵 기본 정보

	vector<vector<shared_ptr<Object>>> _objects; // 맵에 있는 오브젝트

	vector<function<void()>> _openEvent; // 플레이어가 모든 몬스터를 처리했을 때 호출
	vector<function<void()>> _lockEvent; // 플레이어가 몬스터에게 타겟팅이 되었을 때 호출

	bool _clear = false; // 맵에 스폰된 몬스터가 없는지
};