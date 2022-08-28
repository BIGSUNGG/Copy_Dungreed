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

	shared_ptr<BackGround> GetBackGround(int level,int num);
	shared_ptr<Wall> GetWall(int level, int num);
	shared_ptr<Tile> GetTile(int level, int num);

	shared_ptr<Player> GetPlayer(int num);
	shared_ptr<Creature> GetCreature(int level, int num);

	shared_ptr<Bullet> GetPlayerBullet(int type, int num);
	shared_ptr<Weapon> GetPlayerWeapon(int type, int num);

	shared_ptr<Effect> GetPlayerEffect(int num);
	shared_ptr<Effect> GetCreatureEffect(int level, int num);
	shared_ptr<Effect> GetWeaponEffect(int level, int num);

	shared_ptr<Quad> GetCursur(int num);

private:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* _instance;
};

