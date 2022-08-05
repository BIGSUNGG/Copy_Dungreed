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
		CURSUR,
	};

	Object(int level = 0, int num = 0);
	virtual ~Object() {}

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

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
	Object_Type _objectType = Object_Type::TILE;

	int _level;
	int _num;
};

