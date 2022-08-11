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
		EFFECT,
		UI,
	};

	enum State
	{
		IDLE,
		ATTACK,
		MOVE,
		JUMP,
		DIE,
		CHARGE
	};

public:
	Object(int level = 0, int num = 0);
	virtual ~Object() {}

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

	virtual void SetCollider();
	virtual void SetAnimation();
	virtual void SetTexture(shared_ptr<Quad> texture) { _texture = texture; }

	int GetNum() { return _num; }
	int GetLevel() { return _level; }
	bool& GetPlayingAnim() { return _playingAnim; }
	bool& GetIsActive() { return _isActive; }
	Object_Type GetType() { return _objectType; }
	shared_ptr<Quad> GetTexture() { return _texture; }
	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Animation> GetAnimation() { return _anim; }

protected:
	shared_ptr<Quad> _texture;
	shared_ptr<Collider> _collider;
	shared_ptr<Animation> _anim;
	Object_Type _objectType = Object_Type::TILE;

	int _level;
	int _num;

	State _state = IDLE;
	bool _isActive = true;
	bool _playingAnim = false;
};

