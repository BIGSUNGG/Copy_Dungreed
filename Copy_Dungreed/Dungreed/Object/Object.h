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
	class Animation
	{
	public:
		enum Anim_State
		{
			END,
			LOOP,
			PINGPONG,
		};

	public:
		void Update();

		void ChangeAnimation(Object::State state);
		void SetTexture(shared_ptr<Quad> texture) { _texture = texture; }

		vector<vector<wstring>> _animList = vector<vector<wstring>>(6, vector<wstring>());
		vector<vector<float>>   _animSpeed = vector<vector<float>>(6, vector<float>(10, 0.15f));
		vector<Anim_State> _animState = vector<Anim_State>(6, LOOP);

	private:
		shared_ptr<Quad> _texture;
		float _animRunTime = 0.0f;
		bool _isPlaying = true;
		pair<int, int> _index = { 0,0 };
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
	bool _playingAnim = false;
};

