#pragma once
class Object
{
public:
	enum Object_Type
	{
		BACKGROUND,
		WALL,
		TILE,
		CREATURE,
		ECT,
		EFFECT,
		UI,
	};

public:
	Object(int level = 0, int num = 0);
	virtual ~Object() {}

	virtual void Update();
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual void ImGuiRender();

	virtual void ReverseTexture();

	virtual void SetCollider(shared_ptr<RectCollider> collider = nullptr);
	virtual void SetAnimation();
	virtual void SetSpawnPos(Vector2 pos);
	virtual void SetPos(const Vector2& pos) { _texture->GetTransform()->GetPos() = pos; }
	virtual void SetTexture(shared_ptr<Quad> texture);


	bool& GetRender() { return _render; }
	bool& GetCollision() { return _collison; }
	const int& GetNum() { return _num; }
	const int& GetLevel() { return _level; }
	const bool& GetStatic() { return _static; }
	const bool& GetReversed() { return _reversed; }
	const bool& GetIsActive() { return _isActive; }
	const Object_Type& GetType() { return _objectType; }
	Vector2& GetPos() { return _texture->GetTransform()->GetPos(); }
	const Vector2& GetSpawnPos() { return _spawnPos; }
	shared_ptr<Quad> GetObjectTexture() { return _texture; }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	shared_ptr<Animation> GetAnimation() { return _anim; }

	static const int _objectTypeCount = 7;
protected:
	Object_Type _objectType = Object_Type::TILE;
	Vector2 _spawnPos = { 0,0 };
	bool _static = false;
	bool _isActive = true;
	bool _collison = true;

	shared_ptr<Quad> _texture;
	shared_ptr<RectCollider> _collider;
	shared_ptr<Animation> _anim;
	shared_ptr<ObjectBuffer> _buffer;

	int _level = 0;
	int _num = 0;
	bool _render = true;
	bool _reversed = false;

};

