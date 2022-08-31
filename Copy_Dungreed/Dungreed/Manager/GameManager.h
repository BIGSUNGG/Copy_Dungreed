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

	void AddObject(shared_ptr<Object> object, int type,bool toFront = false);
	void AddEffect(shared_ptr<Effect> effect);
	void AddPlayer(shared_ptr<Player> player);
	void AddDebugCollider(shared_ptr<Collider> collider) { _debugCollider.push_back(collider); }

	bool& GetPause() { return _pause; }
	bool& GetRenderTexture() { return _renderTexture; }
	bool& GetRenderCollider() { return _renderCollider; }

	bool& GetObjectUpdate() { return _objectUpdate; }
	vector<shared_ptr<Object>> GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type, bool OBB = false, bool setColor = true);
	vector<shared_ptr<Object>> GetCollisions(Vector2 pos, Object::Object_Type type, bool setColor = true);
	vector<vector<shared_ptr<Object>>>& GetObjects() { return _objects; }
	shared_ptr<Creature> GetPlayer() { return _player; }

private:
	GameManager();
	~GameManager();
	static GameManager* _instance;	
	
	float _maxDelay = 0.1f;

	vector<vector<shared_ptr<Object>>> _objects;
	vector<vector<shared_ptr<Object>>> _optimized;
	vector<shared_ptr<Collider>> _debugCollider;
	shared_ptr<Player> _player;

	bool _renderTexture = true;
	bool _renderCollider = false;
	bool _pause = false;
	bool _objectUpdate = false;
};

