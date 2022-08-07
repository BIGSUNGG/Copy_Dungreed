#pragma once
class Object
{
public:
	struct Animation
	{
		enum State
		{
			END,
			LOOP,
			PINGPONG,
		};

		vector<vector<wstring>> _animList = vector<vector<wstring>>(5, vector<wstring>());
		vector<vector<float>>   _animSpeed = vector<vector<float>>(5, vector<float>(5, 0.2f));
		float _animRunTime = 0.0f;
		pair<int, int> _index = { 0,0 };

		vector<State> _state = vector<State>(5, LOOP);
	};

public:
	enum Object_Type
	{
		BACKGROUND,
		WALL,
		TILE,
		CREATURE,
		EFFECT,
	};

public:
	Object(int level = 0, int num = 0);
	virtual ~Object() {}

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

	virtual void SetCollider();
	virtual void SetTexture(shared_ptr<Quad> texture) { _texture = texture; }

	int GetNum() { return _num; }
	int GetLevel() { return _level; }
	bool& GetPlayingAnim() { return _playingAnim; }
	Object_Type GetType() { return _objectType; }
	shared_ptr<Quad> GetTexture() { return _texture; }
	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Animation>& GetAnimation() { return _anim; }

	bool operator< (const Object& value);
	bool operator> (const Object& value);
	bool operator<= (const Object& value);
	bool operator>= (const Object& value);
protected:
	shared_ptr<Quad> _texture;
	shared_ptr<Collider> _collider;
	shared_ptr<Animation> _anim;
	Object_Type _objectType = Object_Type::TILE;

	int _level;
	int _num;

	bool _playingAnim = false;
};

