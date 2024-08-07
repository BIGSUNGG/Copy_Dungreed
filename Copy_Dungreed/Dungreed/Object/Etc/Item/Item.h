#pragma once

class Creature;

class Item : public Etc
{
public:
	enum Item_Type
	{
		WEAPON,
		SUB_WEAPON,
		ACCESSORY,
		NONE
	};

	enum Item_State
	{
		IDLE,
		ATTACK,
		SKILL,
		DAMAGED,
	};

public:
	Item(int level, int num);
	virtual ~Item();

	virtual void ReverseTexture();
	
	// 공격 시 호출
	virtual void Attack() abstract;
	// 스킬 사용 시 호출
	virtual void Skill() abstract;

public:
	// Getter Setter
	virtual void SetOwner(shared_ptr<Creature> owner);
	void SetIconTexture(const wstring& image);

	shared_ptr<Quad> GetIconTexture() { return _iconTexture; }
	const shared_ptr<Creature> GetOwner() { return _owner.lock(); }
	const Item_Type& GetItemType() { return _itemType; }

protected:
	Item_Type _itemType = ACCESSORY; 

	weak_ptr<Creature> _owner; // 오너 캐릭터
	shared_ptr<Quad> _iconTexture; // 아이템 아이콘 이미지	 
};

