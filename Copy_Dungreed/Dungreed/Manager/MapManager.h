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

	// File
	bool IsMapFileExist(int level, int num);
	wstring GetMapBasicInfoFileWPath(int level, int num);
	string GetMapBasicInfoFileSPath(int level, int num);

	wstring GetMapObjectsFileWPath(int level, int num);
	string GetMapObjectsFileSPath(int level, int num);

	// Save Load
	shared_ptr<Map> Load(int level, int num);
	MapBasic LoadBasicInfo(int level, int num);
	vector<shared_ptr<Object>> LoadObjects(int level, int num, int objectCount);

	void Save(shared_ptr<Map> map);
	void SaveAll();

public:
	// Getter Setter
	void SetCurMap(shared_ptr<Map> map);
	void SetCurMap(const Vector2& index);
	void SetTarget(shared_ptr<Creature> target);

	const Vector2& GetMapIndex() { return _curMapIndex; }
	const map<int, vector<int>>& GetCurMapSize() { return _mapList; }
	const map<int, map<int, pair<shared_ptr<Map>, bool>>>& GetMaps() { return _maps; }
	const shared_ptr<Map>& GetCurMap() { return _maps[_curMapIndex.x][_curMapIndex.y].first; }

private:
	void AddMap(shared_ptr<Map> map, Vector2 where);

private:
	MapManager();
	~MapManager();
	static MapManager* _instance;


	map<int, map<int, pair<shared_ptr<Map>,bool>>> _maps;
	Vector2 _mapSize = { 6,2 };
	int _mapCount = 0;
	const int _mapCountMax = 10;

	Vector2 _curMapIndex = {0,0};
	map<int,vector<int>> _mapList;

	const Vector2 _doorVerticalHalfSize = { 60.0f, 198.0f };
	const Vector2 _doorHorizonlHalfSize = { 198.0f, 60.0f };

};

