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

	shared_ptr<Map> Load(int level, int num);
	void Save(shared_ptr<Map> map);

private:
	MapManager();
	~MapManager();
	static MapManager* _instance;

	unordered_map<int, unordered_map<int, shared_ptr<Map>>> _maps;
	vector<int> _mapSize;
};

