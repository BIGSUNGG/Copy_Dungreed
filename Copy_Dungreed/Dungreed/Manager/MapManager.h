#pragma once
class MapManager
{
public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new MapManager;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static MapManager* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}

	void Update();

public:
	// ���� �̷� �� �����
	// level : ���� ���� ����
	// num : ���� ���� ��ȣ
	void MakeRandomMap(int level,int num);

private:
	// �̷ο� �� �߰�
	void AddMap(shared_ptr<StageMap> map, Vector2 pos);

public:
	// Save Load
	shared_ptr<StageMap> LoadMap(int level, int num);
	StageMapBasic LoadBasicInfo(int level, int num);
	vector<shared_ptr<Object>> LoadObjects(int level, int num, int objectCount);

	void Save(shared_ptr<StageMap> map);
	// ��� �� ����
	void SaveAll();

public:
	// File
	bool IsMapFileExist(int level, int num);
	wstring GetMapBasicInfoFileWPath(int level, int num);
	string GetMapBasicInfoFileSPath(int level, int num);

	wstring GetMapObjectsFileWPath(int level, int num);
	string GetMapObjectsFileSPath(int level, int num);

	// Getter Setter
	void SetCurMap(shared_ptr<StageMap> map);
	void SetCurMap(const Vector2& index);
	void SetTarget(shared_ptr<Creature> target);

	const Vector2& GetMapPos() { return _curMapPos; }
	const unordered_map<int, vector<int>>& GetCurMapSize() { return _mapList; }
	const unordered_map<int, unordered_map<int, shared_ptr<StageMap>>>& GetMaps() { return _maps; }
	const shared_ptr<StageMap>& GetCurMap() { return _maps[_curMapPos.x][_curMapPos.y]; }

private:
	MapManager();
	~MapManager();
	static MapManager* _instance;

	unordered_map<int, unordered_map<int, shared_ptr<StageMap>>> _maps;
	Vector2 _mapHalfSize = { 5,2 };
	int _mapCount = 0;
	const int _mapCountMin = 12;

	Vector2 _curMapPos = {0,0}; // ���� �÷��̾ �ִ� �� ��ġ
	unordered_map<int,vector<int>> _mapList; // Save ������ �ִ� �� ���� ���

	const Vector2 _doorVerticalHalfSize = { 60.0f, 198.0f };
	const Vector2 _doorHorizonlHalfSize = { 198.0f, 60.0f };

};

