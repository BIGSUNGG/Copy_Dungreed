#pragma once
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

	void SetObjects(vector<vector<shared_ptr<Object>>>* objects) { _objects = objects; }

	vector<shared_ptr<Object>> GetCollisions(shared_ptr<Collider>& collider , Object::Object_Type type);

private:
	GameManager();
	~GameManager();
	static GameManager* _instance;	
	
	static vector<vector<shared_ptr<Object>>>* _objects;
};

