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
	};

	enum State
	{
		IDLE,
		ATTACK,
		RUN,
		JUMP,
		DIE,
		CHARGE
	};

public:
	Object(int level, int num);
	virtual ~Object() {}

	virtual void Update();
	virtual void Render();
	virtual void PostRender();
	virtual void ImGuiRender();

	virtual void ReverseTexture();

	virtual void SetCollider();
	virtual void SetAnimation();
	virtual void SetSpawnPos(Vector2 pos);
	virtual void SetPos(const Vector2& pos) { _texture->GetTransform()->GetPos() = pos; }
	virtual void SetTexture(shared_ptr<Quad> texture);


	const int& GetNum() { return _num; }
	const int& GetLevel() { return _level; }
	const bool& GetPlayingAnim() { return _playingAnim; }
	const bool& GetReversed() { return _reversed; }
	const bool& GetIsActive() { return _isActive; }
	const Object_Type& GetType() { return _objectType; }
	const Vector2& GetPos() { return _texture->GetTransform()->GetPos(); }
	shared_ptr<Quad> GetTexture() { return _texture; }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	shared_ptr<Animation> GetAnimation() { return _anim; }

protected:
	shared_ptr<Quad> _texture;
	shared_ptr<RectCollider> _collider;
	shared_ptr<Animation> _anim;
	Object_Type _objectType = Object_Type::TILE;

	int _level;
	int _num;

	State _state = IDLE;
	bool _isActive = true;
	bool _playingAnim = false;
	bool _reversed = false;
};

