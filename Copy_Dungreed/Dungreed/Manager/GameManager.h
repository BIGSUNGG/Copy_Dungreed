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

	// 매 틱마다 호출
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ImguiRender();

	// 입력 이벤트
	void Input();

	// 게임 최적화 코드
	void Optimize();

	// 인스턴싱 텍스쳐
	void AddInstanceQuad(shared_ptr<Object> object);
	void DeleteInstanceQuad(shared_ptr<Object> object);	

	// 오브젝트
	void SetPlayer(shared_ptr<Player> player);
	void AddEffect(shared_ptr<Effect> effect);
	void AddEtcObject(shared_ptr<Object> object);
	void AddDebugCollider(shared_ptr<Collider> collider);

	void AddObject(shared_ptr<Object> object, int type);
	void DeleteObject(shared_ptr<Object> deleteObject);

	// 초기화
	void Reset();
	void ResetPlayer();
public:
	// Getter Setter
	bool GetPause() { return _pause; }
	bool GetRenderTexture() { return _enableRenderTexture; }
	bool GetRenderCollider() { return _enableRenderCollider; }
	bool GetRenderUI() { return _enableRenderUI; }
	const vector<vector<shared_ptr<Object>>>& GetObjects() { return _curMap->GetObjects(); }

	bool GetPlaying() { return _playing; }
	vector<shared_ptr<Object>> GetCollisions(shared_ptr<Collider> collider, Object::Object_Type type, bool OBB = false, bool setColor = true , bool forceCollision = false);
	vector<shared_ptr<Object>> GetCollisions(Vector2 pos, Object::Object_Type type, bool setColor = true);
	shared_ptr<Player> GetPlayer() { return _player; }
	shared_ptr<StageMap> GetCurMap() { return _curMap; }

	void SetRenderTexture(bool value) { _enableRenderTexture = value; }
	void SetRenderCollider(bool value) { _enableRenderCollider = value; }
	void SetRenderUI(bool value) { _enableRenderUI = value; }
	void SetEnableUI(bool value) { _enableUI = value; }
	void SetPause(bool value) { _pause = value; }
	void SetPlaying(bool value) { _playing = value; }
	void SetCurMap(shared_ptr<StageMap> addedMap);
	void SetInput(bool input) { _enableInput = input; }

private:
	GameManager();
	~GameManager();
	static GameManager* _instance;	
	
	const float _maxDeltaTime = 0.05f; // DeltaTime이 해당 값을 넘으면 해당 틱 무시
	const float _drawColliderTime = 1.f; // 공격 범위 그리기 시간
	vector<pair<shared_ptr<Collider>/*그릴 콜라이더*/, float/*남은 그릴 시간*/>> _drawCollider; // 그릴 공격 콜라이더 배열

	shared_ptr<StageMap> _curMap; // 현재 플레이 중인 맵
	vector<unordered_map<wstring/*텍스쳐 이름*/, shared_ptr<InstanceQuad>>> instanceQuads; // 인스턴싱된 텍스쳐 모음

	shared_ptr<Player> _player; // 플레이어 캐릭터

	bool _enableInput = true; // 입력을 활성화할지 
	bool _enableRenderTexture = true; // 텍스쳐를 렌더링할지
	bool _enableRenderCollider = false; // 콜라이더를 렌더링할지
	bool _enableRenderUI = true; // UI를 렌더링할지
	bool _enableUI = false; // UI를 사용할지
	bool _pause = false; // 게임이 정지 중인지
	bool _playing = false; // 게임이 플레이 중인지 (false시 오브젝트들이 움직이지 않음)

	bool _enableInstancing = true; // 인스턴싱된 텍스쳐를 사용할지
	bool _enableFrustum = true; // 프러스텀 컬링을 사용할지
	float _frustumSizeRatio = 1.f; // 프러스텀 컬링할 콜라이더의 크기 비율
};

