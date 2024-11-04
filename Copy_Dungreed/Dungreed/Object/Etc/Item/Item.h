#pragma once

class Creature;

enum class Item_Type
{
	WEAPON,
	SUB_WEAPON,
	ACCESSORY,
	NONE
};

enum Item_State : int
{
	IDLE,
	ATTACK,
	SKILL,
	DAMAGED,
};

class Item : public Etc
{
public:
	Item(int level, int num);
	virtual ~Item();

	virtual void ReverseTexture();
	
	// ���� �� ȣ��
	virtual void Attack() abstract;
	// ��ų ��� �� ȣ��
	virtual void Skill() abstract;

public:
	// Getter Setter
	virtual void SetOwner(shared_ptr<Creature> owner);
	void SetIconTexture(const wstring& image);

	shared_ptr<Quad> GetIconTexture() { return _iconTexture; }
	const shared_ptr<Creature> GetOwner() { return _owner.lock(); }
	const Item_Type& GetItemType() { return _itemType; }

protected:
	Item_Type _itemType = Item_Type::ACCESSORY;

	weak_ptr<Creature> _owner; // ���� ĳ����
	shared_ptr<Quad> _iconTexture; // ������ ������ �̹���	 
};

