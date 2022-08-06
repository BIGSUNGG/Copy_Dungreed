#pragma once
class Object
{
protected:
	struct Animation
	{
		enum State
		{
			END,
			LOOP,
			PINGPONG,
		};

		vector<vector<wstring>> _animList;
		vector<vector<float>>   _animSpeed;
		float _animRunTime = 0.0f;
		pair<int, int> _index = { 0,0 };

		State _state = LOOP;
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

	Object(int level = 0, int num = 0);
	virtual ~Object() {}

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

	virtual void SetCollider();
	virtual void SetTexture(shared_ptr<Quad> texture) { _texture = texture; }

	virtual int GetNum() { return _num; }
	virtual int GetLevel() { return _level; }
	virtual Object_Type GetType() { return _objectType; }
	virtual shared_ptr<Quad> GetTexture() { return _texture; }
	virtual shared_ptr<Collider> GetCollider() { return _collider; }

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

