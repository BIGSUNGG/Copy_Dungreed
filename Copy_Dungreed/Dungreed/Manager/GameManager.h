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
	void Instancing();

	void AddObject(shared_ptr<Object> object, int type,bool toFront = false);
	void AddEffect(shared_ptr<Effect> effect);
	void AddPlayer(shared_ptr<Player> player);
	void AddEctObject(shared_ptr<Object> object);
	void AddDebugCollider(shared_ptr<Collider> collider) { _debugCollider.push_back(collider); }

	bool& GetPause() { return _pause; }
	bool& GetRenderTexture() { return _renderTexture; }
	bool& GetRenderCollider() { return _renderCollider; }

	bool& GetObjectUpdate() { return _objectUpdate; }
	vector<shared_ptr<Object>> GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type, bool OBB = false, bool setColor = true , bool forceCollision = false);
	vector<shared_ptr<Object>> GetCollisions(Vector2 pos, Object::Object_Type type, bool setColor = true);
	shared_ptr<Player> GetPlayer() { return _player; }

	void SetMap(shared_ptr<Map> addedMap);

	void Reset();

private:
	GameManager();
	~GameManager();
	static GameManager* _instance;	
	
	const float _maxDelay = 0.05f;

	shared_ptr<Map> _curMap;
	vector<vector<shared_ptr<InstanceQuad>>> _instanceQuad;
	vector<vector<shared_ptr<Object>>> _objectInScreen;
	vector<shared_ptr<Collider>> _debugCollider;
	shared_ptr<Player> _player;

	bool _renderTexture = true;
	bool _renderCollider = false;
	bool _pause = false;
	bool _objectUpdate = false;
};

