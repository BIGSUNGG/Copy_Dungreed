#pragma once
class UIManager
{
public:
	enum class UI_State
	{
		NOMAL,
		INVEN,
		MAP,
		OPTION,
		SETTING,
	};

	enum Blink_State
	{
		END = 0b00000000,
		DARK = 0b00000010,
		BRIGHT = 0b00000100,
	};

public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new UIManager;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static UIManager* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}
	
	void Update();
	void PreRender();
	void PostRender();

	void Refresh();
	void SetState(const UI_State& state);
	const UI_State& GetCurState() { return _state; }
	char GetBlinkState() { return _blinkState; }

	void Blink(const float& speed, const XMFLOAT4& color, function<void()> func = nullptr);

private:
	UIManager();
	~UIManager();

	static UIManager* _instance;
	UI_State _state = UI_State::NOMAL;
	shared_ptr<RenderTarget> _filter;
	shared_ptr<Quad> _filterQuad;

	shared_ptr<Quad> _blinkQuad;
	shared_ptr<RenderTarget> _blinkRtv;
	XMFLOAT4 _blinkColor;
	float _blinkSpeed;
	char _blinkState;
	function<void()> _blinkEvent;


	vector<shared_ptr<UI>> _ui;

	shared_ptr<UI_MiniMap> _miniMap;
	shared_ptr<UI_PlayerHpBar> _playerHpBar;
	shared_ptr<UI_EnemyHpBar> _enemyHpBar;
	shared_ptr<UI_WeaponSlot> _weaponSlot;
	shared_ptr<UI_Info> _info;
	shared_ptr<UI_Inventory> _inventory;
	shared_ptr<UI_Map> _map;
	shared_ptr<UI_Option> _select;
	shared_ptr<UI_Setting> _setting;

};

