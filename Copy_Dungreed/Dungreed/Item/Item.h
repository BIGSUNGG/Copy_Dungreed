#pragma once

class Creature;

class Item
{
public:
	enum Item_Type
	{
		PLAYER,
		FOOD,
		WEAPON,
		ACCESSORY,
	};

	enum Item_State
	{
		IDLE,
		ATTACK,
		SKILL,
		DAMAGED,
	};

public:
	Item();
	virtual ~Item();

	virtual void Update();
	virtual void Render();

	virtual void ReverseTexture();

	virtual void Attack() abstract;
	virtual void Skill() abstract;
	virtual void Damaged(const Status& status) abstract;

	virtual void SetOwner(shared_ptr<Creature> owner);
	virtual void SetAnimation();
	virtual void SetTexture(shared_ptr<Quad> texture);

	const bool& GetPlayingAnim() { return _playingAnim; }
	const bool& GetIsActive() { return _isActive; }
	const bool& GetReversed() { return _reversed; }
	const Item_Type& GetItemType() { return _itemType; }
	virtual shared_ptr<Quad> GetTexture() { return _texture; }
	shared_ptr<Animation> GetAnimation() { return _anim; }

protected:
	weak_ptr<Creature> _owner;
	shared_ptr<Quad> _texture;
	shared_ptr<Animation> _anim;

	Status _status;

	Item_Type _itemType = ACCESSORY;

	Item_State _state = IDLE;
	bool _isActive = true;
	bool _playingAnim = false;
	bool _reversed = false;

};

