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

	void Input();

	void AddObject(shared_ptr<Object> object, int type);
	void AddEffect(shared_ptr<Effect> effect);
	void AddPlayer(shared_ptr<Player> player);
	void AddEctObject(shared_ptr<Object> object);
	void AddDebugCollider(shared_ptr<Collider> collider);

	void DeleteObject(shared_ptr<Object> deleteObject);

	bool& GetPause() { return _pause; }
	bool& GetRenderTexture() { return _renderTexture; }
	bool& GetRenderCollider() { return _renderCollider; }
	const vector<vector<shared_ptr<Object>>>& GetObjects() { return _curMap->GetObjects(); }

	bool& GetPlaying() { return _playing; }
	vector<shared_ptr<Object>> GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type, bool OBB = false, bool setColor = true , bool forceCollision = false);
	vector<shared_ptr<Object>> GetCollisions(Vector2 pos, Object::Object_Type type, bool setColor = true);
	shared_ptr<Player> GetPlayer() { return _player; }

	void SetCurMap(shared_ptr<Map> addedMap);
	void SetInput(bool input) { _input = input; }

	void Reset();

private:
	GameManager();
	~GameManager();
	static GameManager* _instance;	
	
	const float _maxDelay = 0.05f;
	const float _debugColliderRunTime = 1.f;

	shared_ptr<Map> _curMap;

	map<float, pair<vector<shared_ptr<Object>>, vector<shared_ptr<InstanceQuad>>>> _renderOrder;
	vector<vector<shared_ptr<Object>>> _objectInScreen;
	vector<pair<shared_ptr<Collider>,float>> _debugCollider;

	shared_ptr<Player> _player;

	bool _input = true;
	bool _renderTexture = true;
	bool _renderCollider = false;
	bool _pause = false;
	bool _playing = false;
};

