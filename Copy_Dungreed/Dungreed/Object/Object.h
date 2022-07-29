#pragma once
class Object
{
public:
	enum class Type
	{
		BACKGROUND,
		CREATURE,
		EFFECT,
		TILE,
		ECT,
		UI,
	};

	Object();
	virtual ~Object() {}

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

	virtual Type GetType() { return _type; }
	virtual shared_ptr<Quad> GetTexture() { return _texture; }
	virtual shared_ptr<Collider> GetCollider() { return _collider; }

	bool operator< (const Object& value);
	bool operator> (const Object& value);
	bool operator<= (const Object& value);
	bool operator>= (const Object& value);
protected:
	shared_ptr<Quad> _texture;
	shared_ptr<Collider> _collider;
	Type _type = Type::ECT;
};

