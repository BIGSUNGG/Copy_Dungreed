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

	// ��� ���Ͱ� óġ�Ǿ�����
	bool CheckClear();

public:
	// ������Ʈ
	void AddObject(shared_ptr<Object> addObject, int type);
	bool DeleteObject(shared_ptr<Object> deleteObject);
	bool DeleteObject(shared_ptr<Object> deleteObject, int type);

	// ��	
	// �� ��ü�� copyMap�� ����
	void Paste(shared_ptr<StageMap> copyMap);
	// �� �ʱ�ȭ
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
	StageMapBasic _mapBasicInfo; // �� �⺻ ����

	vector<vector<shared_ptr<Object>>> _objects; // �ʿ� �ִ� ������Ʈ

	vector<function<void()>> _openEvent; // �÷��̾ ��� ���͸� ó������ �� ȣ��
	vector<function<void()>> _lockEvent; // �÷��̾ ���Ϳ��� Ÿ������ �Ǿ��� �� ȣ��

	bool _clear = false; // �ʿ� ������ ���Ͱ� ������
};