#pragma once
class Bullet
{
public:
	Bullet();
	virtual ~Bullet();

	void Update();
	void Render();
	void PostRender();

	void ReverseTexture();
	virtual void Attack();
	virtual void DestroyEvent();

	virtual void SetCollider();
	virtual void SetAnimation();
	virtual void SetTexture(shared_ptr<Quad> texture);
	virtual void SetSpeed(float speed) { _speed = speed; }
	virtual void SetDirection(const Vector2& direction) { _direction = direction; }
	virtual void SetOwner(shared_ptr<Creature> owner) { _owner = owner; }

	const bool& GetPlayingAnim() { return _playingAnim; }
	const bool& GetIsActive() { return _isActive; }
	shared_ptr<Quad> GetTexture() { return _texture; }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	shared_ptr<Animation> GetAnimation() { return _anim; }

protected:
	shared_ptr<Quad> _texture;
	shared_ptr<RectCollider> _collider;
	shared_ptr<Animation> _anim;
	weak_ptr<Creature> _owner;

	bool _isActive = true;
	bool _playingAnim = false;

	float _runTime = 0.0f;
	float _runTimeMax = 1.0f;
	float _speed = 0.0f;
	Vector2 _direction;
};

