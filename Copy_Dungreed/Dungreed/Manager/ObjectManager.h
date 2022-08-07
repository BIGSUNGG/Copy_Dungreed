#pragma once
class ObjectManager
{
public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new ObjectManager;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static ObjectManager* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}

	shared_ptr<Object> GetNewObject(int type, int level, int num);

	shared_ptr<BackGround> GetBackGroundObject(int level,int num);
	shared_ptr<Tile> GetTileObject(int level, int num);
	shared_ptr<Creature> GetCreature(int level, int num);

private:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* _instance;
};

