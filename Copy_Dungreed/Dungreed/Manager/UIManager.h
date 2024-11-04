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
		END,
		DARK,
		STOP,
		BRIGHT,
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
	void ImGuiRender();

	void Refresh();

	// ȭ�� �����̱�
	// speed : �����̴� �ӵ�
	// stopTime : �Ϻ��� ��ο����� ��ٸ��� �ð�
	// color : ��ο����� ��
	// func : �Ϻ��� ��ο����� ȣ���� �Լ�
	bool Blink(const float& speed, const float& stopTime = 0, const XMFLOAT4& color = {0,0,0,0}, function<void()> func = nullptr);

public:
	// Getter Setter
	char GetBlinkState() { return _blinkState; }
	const UI_State& GetCurState() { return _state; }
	bool GetShowAllMaps() { return _showAllMaps; }

	void SetState(const UI_State& state);
	void SetPostProssesing(XMFLOAT4 color);

private:
	UIManager();
	~UIManager();

	static UIManager* _instance;
	UI_State _state = UI_State::NOMAL;
	shared_ptr<RenderTarget> _postProssessing;
	shared_ptr<Quad> _postProssessingQuad;

	// Blink
	shared_ptr<Quad> _blinkQuad;
	shared_ptr<RenderTarget> _blinkRtv;
	XMFLOAT4 _blinkColor;
	float _blinkSpeed;
	float _blinkStop;
	char _blinkState = END;
	function<void()> _blinkEvent;

	// UI
	vector<shared_ptr<UI>> _uiList;
	shared_ptr<UI_MiniMap> _miniMap;
	shared_ptr<UI_PlayerHpBar> _playerHpBar;
	shared_ptr<UI_EnemyHpBar> _enemyHpBar;
	shared_ptr<UI_WeaponSlot> _weaponSlot;
	shared_ptr<UI_Info> _info;
	shared_ptr<UI_Inventory> _inventory;
	shared_ptr<UI_Map> _map;
	shared_ptr<UI_Option> _select;
	shared_ptr<UI_Setting> _setting;

	bool _showAllMaps = false; // �������� �湮�� ������ ������� ������ ������
};

