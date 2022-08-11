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

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ImguiRender();

	void Optimize();

	vector<shared_ptr<Object>> GetCollisions(shared_ptr<Collider> collider , Object::Object_Type type,bool setColor = true);
	vector<vector<shared_ptr<Object>>>& GetObjects() { return _objects; }

private:
	GameManager();
	~GameManager();
	static GameManager* _instance;	
	
	float _maxDelay = 0.1f;
	vector<vector<shared_ptr<Object>>> _objects;
	vector<vector<shared_ptr<Object>>> _optimized;
};

