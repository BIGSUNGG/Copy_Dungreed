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

	// �� ƽ���� ȣ��
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ImguiRender();

	// �Է� �̺�Ʈ
	void Input();

	// ���� ����ȭ �ڵ�
	void Optimize();

	// �ν��Ͻ� �ؽ���
	void AddInstanceQuad(shared_ptr<Object> object);
	void DeleteInstanceQuad(shared_ptr<Object> object);	

	// ������Ʈ
	void SetPlayer(shared_ptr<Player> player);
	void AddEffect(shared_ptr<Effect> effect);
	void AddEtcObject(shared_ptr<Object> object);
	void AddDebugCollider(shared_ptr<Collider> collider);

	void AddObject(shared_ptr<Object> object, int type);
	void DeleteObject(shared_ptr<Object> deleteObject);

	// �ʱ�ȭ
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
	
	const float _maxDeltaTime = 0.05f; // DeltaTime�� �ش� ���� ������ �ش� ƽ ����
	const float _drawColliderTime = 1.f; // ���� ���� �׸��� �ð�
	vector<pair<shared_ptr<Collider>/*�׸� �ݶ��̴�*/, float/*���� �׸� �ð�*/>> _drawCollider; // �׸� ���� �ݶ��̴� �迭

	shared_ptr<StageMap> _curMap; // ���� �÷��� ���� ��
	vector<unordered_map<wstring/*�ؽ��� �̸�*/, shared_ptr<InstanceQuad>>> instanceQuads; // �ν��Ͻ̵� �ؽ��� ����

	shared_ptr<Player> _player; // �÷��̾� ĳ����

	bool _enableInput = true; // �Է��� Ȱ��ȭ���� 
	bool _enableRenderTexture = true; // �ؽ��ĸ� ����������
	bool _enableRenderCollider = false; // �ݶ��̴��� ����������
	bool _enableRenderUI = true; // UI�� ����������
	bool _enableUI = false; // UI�� �������
	bool _pause = false; // ������ ���� ������
	bool _playing = false; // ������ �÷��� ������ (false�� ������Ʈ���� �������� ����)

	bool _enableInstancing = true; // �ν��Ͻ̵� �ؽ��ĸ� �������
	bool _enableFrustum = true; // �������� �ø��� �������
	float _frustumSizeRatio = 1.f; // �������� �ø��� �ݶ��̴��� ũ�� ����
};

