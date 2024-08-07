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

	// 오브젝트
	shared_ptr<Object> GetNewObject(int type, int level, int num);

	shared_ptr<BackGround> GetBackGround(int level,int num);
	shared_ptr<Wall> GetWall(int level, int num);
	shared_ptr<Tile> GetTile(int level, int num);
	shared_ptr<Etc> GetEtc(int type, int num);

	shared_ptr<Player> GetPlayer(int num);
	shared_ptr<Creature> GetCreature(int level, int num);

	// 투사체
	shared_ptr<Bullet> GetBullet(int type, int num);
	
	// 플레이어 아이템
	shared_ptr<Weapon> GetPlayerWeapon(int type, int num);
	shared_ptr<SubWeapon> GetPlayerSubWeapon(int num);
	shared_ptr<Accessory> GetPlayerAccessory(int num);

	// 몬스터 아이템
	shared_ptr<Weapon> GetEnemyWeapon(int type, int num);

	// 이펙트
	shared_ptr<Effect> GetPlayerEffect(int num);
	shared_ptr<Effect> GetCreatureEffect(int level, int num);
	shared_ptr<Effect> GetPlayerWeaponEffect(int level, int num);
	shared_ptr<Effect> GetEnemyWeaponEffect(int level, int num);

	// 골드
	shared_ptr<DropGold> GetGold(int num);

	// 이미지
	wstring GetCursurImage(int num);
	wstring GetNumberImage(int num);

private:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* _instance;
};

