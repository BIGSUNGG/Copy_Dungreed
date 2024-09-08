#pragma once
class InventoryManager
{
public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new InventoryManager;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static InventoryManager* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}

	virtual void Reset();

	// ��� ����
	virtual void IncreaseGold(int value);
	virtual void DecreaseGold(int value);

	// ��� ����
	virtual void IncreaseHungry(int value);
	virtual void DecreaseHungry(int value);

public:
	// Getter Setter
	void SetCurWeaponSlot(int* slot) { _curWeaponSlot = slot; }
	void SetItemSlot(vector<shared_ptr<Item>>* slot) { _itemSlot = slot; }
	void SetWeaponSlot(vector<shared_ptr<Weapon>>* slot) { _weaponSlot = slot; }
	void SetAccessorySlot(vector<shared_ptr<Accessory>>* slot) { _accessory = slot; }

	const int& GetCurGold() { return _curGold; }
	const int& GetCurHungry() { return _curHungry; }
	const int& GetHungryMax() { return _maxHungry; }
	const int& GetPlayerLevel() { return _curPlayerLevel; }
	const int& GetCurWeaponSlot() { return *_curWeaponSlot; }
	const float& GetInteractionDistance() { return _interactionDistance; }
	shared_ptr<Weapon> GetCurWeapon() { return _weaponSlot->operator[](*_curWeaponSlot); }

	vector<shared_ptr<Item>>& GetItemSlot() { return *_itemSlot; }
	vector<shared_ptr<Weapon>>& GetWeaponSlot() { return *_weaponSlot; }
	vector<shared_ptr<Accessory>>& GetAccessorySlot() { return *_accessory; }

private:
	InventoryManager();
	~InventoryManager();

	static InventoryManager* _instance;

	float _interactionDistance = 300.f; // ��ȣ�ۿ� ������ �Ÿ�

	int _curGold = 0; // ���� ��� ��
	int _curHungry = 100; // ���� ��� ��
	int _maxHungry = 100; // �ִ� ��� ��
	int _curPlayerLevel = 12; // ���� �÷��̾� ����

	int* _curWeaponSlot; // ���� ����ִ� ���� ����
	vector<shared_ptr<Weapon>>* _weaponSlot = nullptr; // �÷��̾��� ���� ���� 
	vector<shared_ptr<Accessory>>* _accessory = nullptr; // �÷��̾��� �Ǽ��縮 ����
	vector<shared_ptr<Item>>* _itemSlot = nullptr; // ������ ����
};

