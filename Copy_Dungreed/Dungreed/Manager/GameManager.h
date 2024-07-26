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

	// 게임 최적화 코드
	void Optimize();
	void Instancing();

	void Input();

	void AddObject(shared_ptr<Object> object, int type);
	void AddEffect(shared_ptr<Effect> effect);
	void SetPlayer(shared_ptr<Player> player);
	void ResetPlayer();
	void AddEtcObject(shared_ptr<Object> object);
	void AddDebugCollider(shared_ptr<Collider> collider);

	void DeleteObject(shared_ptr<Object> deleteObject);

public:
	// Getter Setter
	bool GetPause() { return _pause; }
	bool GetRenderTexture() { return _renderTexture; }
	bool GetRenderCollider() { return _renderCollider; }
	bool GetRenderUI() { return _renderUI; }
	const vector<vector<shared_ptr<Object>>>& GetObjects() { return _curMap->GetObjects(); }

	bool GetPlaying() { return _playing; }
	vector<shared_ptr<Object>> GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type, bool OBB = false, bool setColor = true , bool forceCollision = false);
	vector<shared_ptr<Object>> GetCollisions(Vector2 pos, Object::Object_Type type, bool setColor = true);
	shared_ptr<Player> GetPlayer() { return _player; }
	shared_ptr<Map> GetCurMap() { return _curMap; }

	void SetRenderTexture(bool value) { _renderTexture = value; }
	void SetRenderCollider(bool value) { _renderCollider = value; }
	void SetRenderUI(bool value) { _renderUI = value; }
	void SetEnableUI(bool value) { _enableUI = value; }
	void SetPause(bool value) { _pause = value; }
	void SetPlaying(bool value) { _playing = value; }
	void SetCurMap(shared_ptr<Map> addedMap);
	void SetInput(bool input) { _input = input; }

	void Reset();

private:
	GameManager();
	~GameManager();
	static GameManager* _instance;	
	
	const float _maxDeltaTime = 0.05f;
	const float _debugColliderRunTime = 1.f;

	shared_ptr<Map> _curMap;

	map<float, pair<vector<shared_ptr<Object>>, vector<shared_ptr<InstanceQuad>>>> _renderOrder;
	vector<pair<shared_ptr<Collider>,float>> _debugCollider;

	shared_ptr<Player> _player;

	bool _input = true;
	bool _renderTexture = true;
	bool _renderCollider = false;
	bool _renderUI = true;
	bool _enableUI = false;
	bool _pause = false;
	bool _playing = false;

	bool _instancing = true;
	float _frustumSizeRatio = 1.f;
};

