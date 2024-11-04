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

public:
	// 정보 초기화
	virtual void Reset();

	// 골드 증감
	virtual void IncreaseGold(int value);
	virtual void DecreaseGold(int value);

	// 허기 증감
	virtual void IncreaseHungry(int value);
	virtual void DecreaseHungry(int value);

public:
	// Getter Setter
	FORCEINLINE const int& GetCurGold() { return _curGold; }
	FORCEINLINE const int& GetCurHungry() { return _curHungry; }
	FORCEINLINE const int& GetHungryMax() { return _maxHungry; }
	FORCEINLINE const int& GetPlayerLevel() { return _curPlayerLevel; }
	FORCEINLINE const float& GetInteractionDistance() { return _interactionDistance; }

	FORCEINLINE const int& GetCurWeaponSlot() { return GAME->GetPlayer()->GetCurWeaponSlotIndex(); }
	FORCEINLINE shared_ptr<Weapon> GetCurWeapon() { return GAME->GetPlayer()->GetCurWeapon(); }
	FORCEINLINE const shared_ptr<Inventory>& GetInventory() { return GAME->GetPlayer()->GetInventory(); }
	FORCEINLINE const vector<shared_ptr<Item>>& GetItemSlot() { return GAME->GetPlayer()->GetInventory()->GetItemSlot(); }
	FORCEINLINE const vector<shared_ptr<Weapon>>& GetWeaponSlot() { return GAME->GetPlayer()->GetInventory()->GetWeaponSlot(); }
	FORCEINLINE const vector<shared_ptr<Accessory>>& GetAccessorySlot() { return GAME->GetPlayer()->GetInventory()->GetAccessorySlot(); }

private:
	InventoryManager();
	~InventoryManager();

	static InventoryManager* _instance;

	float _interactionDistance = 300.f; // 상호작용 가능한 거리

	int _curGold = 0; // 현재 골드 값
	int _curHungry = 100; // 현재 허기 값
	int _maxHungry = 100; // 최대 허기 값
	int _curPlayerLevel = 12; // 현재 플레이어 레벨
};

