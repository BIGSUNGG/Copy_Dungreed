#pragma once

class Player;

class Item
{
public:
	enum Item_Type
	{
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
	Item(int type, int num);
	virtual ~Item();

	virtual void Update();
	virtual void Render();

	virtual void ReverseTexture();

	virtual void Attack() abstract;
	virtual void Skill() abstract;
	virtual void Damaged(const Status& status) abstract;

	virtual void SetOwner(shared_ptr<Player> owner);
	virtual void SetAnimation();
	virtual void SetTexture(shared_ptr<Quad> texture);

	int GetNum() { return _num; }
	int GetType() { return _type; }
	bool& GetPlayingAnim() { return _playingAnim; }
	bool& GetIsActive() { return _isActive; }
	bool& GetReversed() { return _reversed; }
	virtual Item_Type GetItemType() { return _itemType; }
	virtual shared_ptr<Quad> GetTexture() { return _texture; }
	shared_ptr<Animation> GetAnimation() { return _anim; }

protected:
	shared_ptr<Player> _owner;
	shared_ptr<Quad> _texture;
	shared_ptr<Animation> _anim;

	Status _status;

	Item_Type _itemType = ACCESSORY;

	int _type;
	int _num;

	Item_State _state = IDLE;
	bool _isActive = true;
	bool _playingAnim = false;
	bool _reversed = false;

};

