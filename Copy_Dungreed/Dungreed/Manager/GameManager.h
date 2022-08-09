#pragma once

class GameMode;
class Dungreed;

class GameManager
{
public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new GameManager;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static GameManager* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}

	shared_ptr<Player> GetPlayer();

	vector<shared_ptr<Object>> GetCollisions(shared_ptr<Collider> collider , Object::Object_Type type);

	void SetObjects(vector<vector<shared_ptr<Object>>>* objects) { _objects = objects; }

private:
	GameManager();
	~GameManager();
	static GameManager* _instance;	
	
	static vector<vector<shared_ptr<Object>>>* _objects;
};

