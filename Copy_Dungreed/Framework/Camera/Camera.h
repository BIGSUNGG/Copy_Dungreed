#pragma once
class Camera
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Camera();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Camera* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	void Update();
	void ImGuiRender();

	void ShakeStart(float magnitude, float duration, float reduceDamping = 1.0f);
	
public:
	// Getter Setter
	void SetViewPort(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetProjectionBuffer(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetCameraWorldBuffer() { _transform->SetBuffer(1); }
	void SetUiCameraBuffer() { _uiCameraBuffer->SetVSBuffer(1); }

	void SetTarget(shared_ptr<Transform> target) { _target = target; }
	void SetLeftBottom(Vector2 value) { _leftBottom = value; }
	void SetRightTop(Vector2 value) { _rightTop = value; }
	void SetFreeMode(bool value) { _freeMode = value; }

	shared_ptr<Transform> GetMoveTransform() { return _moveTransform; }
	shared_ptr<Transform> GetTransform() { return _transform; }
	const Vector2& GetVelocity() { return _velocity; }
	const Vector2& GetBeforeMove() { return _beforeMove; }
	Vector2 GetPos() { return _transform->GetPos() * -1; }
	Vector2 GetLeftBottom() { return _leftBottom; }
	Vector2 GetRightTop() { return _rightTop; }

	Vector2 GetMouseWorldPos();

	bool GetFreeMode() { return _freeMode; }

private:
	void Shake();
	void FreeMode();
	void FollowMode();

	Camera();
	~Camera();

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _moveTransform;
	shared_ptr<MatrixBuffer> _projectionBuffer;
	shared_ptr<MatrixBuffer> _uiCameraBuffer;

	float _controlSpeed= 2000.0f;
	float _followSpeed = 200.0f;
	
	shared_ptr<Transform> _target;
	Vector2 _offset = Vector2(CENTER.x,CENTER.y - 40);
	bool _freeMode = false;

	Vector2 _leftBottom = { 0.f,0.f };
	Vector2 _rightTop = { 0.f,0.f };

	float _duration = 0.0f;
	float _reduceDamping = 0.0f;
	float _magnitude = 0.0f;

	Vector2 _originPos = { 0.0f,0.0f };
	Vector2 _beforeMove;
	Vector2 _velocity;

	static Camera* _instance;
};

