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

	void MakeRandomMap(int level,int num);
	void FindTopMap(int level, int x, int y);
	void FindBottomMap(int level, int x, int y);
	void FindLeftMap(int level, int x, int y);
	void FindRightMap(int level, int x, int y);

	shared_ptr<Map> Load(int level, int num);
	void Save(shared_ptr<Map> map);
	void SaveAll();

	void SetTarget(shared_ptr<Creature> target);
	void SetCurMap(shared_ptr<Map> map);
	void SetCurMap(const Vector2& index);

	const shared_ptr<Map>& GetCurMap() { return _maps[_curMapIndex.x][_curMapIndex.y]; }
	const vector<vector<int>>& GetCurMapSize() { return _mapSize; }

private:
	MapManager();
	~MapManager();
	static MapManager* _instance;

	unordered_map<int, unordered_map<int, shared_ptr<Map>>> _maps;
	Vector2 _curMapIndex = {0,0};
	vector<vector<int>> _mapSize;
	string _path;

	const Vector2 _doorHalfSize = { 48.0f, 192.0f };
};

