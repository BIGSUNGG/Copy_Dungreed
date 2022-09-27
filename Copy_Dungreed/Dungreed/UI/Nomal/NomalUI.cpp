#include "framework.h"
#include "NomalUI.h"

NomalUI::NomalUI()
	: UI()
{
	_uiType = UI::GROUND;

	_cursur = OBJ_MANAGER->GetCursur(2);

	_hpBarEmpty = make_shared<Object>();
	_hpBarEmpty->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/HpBar_Empty.png"));
	_hpBarEmpty->GetTexture()->SetLeft(18);
	_hpBarEmpty->GetTexture()->SetTop(WIN_HEIGHT - 18);
	_hpBarEmpty->SetSpawnPos(_hpBarEmpty->GetPos());

	_hpBarBase = make_shared<Object>();
	_hpBarBase->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/HpBar_Base.png"));
	_hpBarBase->GetTexture()->SetLeft(18);
	_hpBarBase->GetTexture()->SetTop(WIN_HEIGHT - 18);
	_hpBarBase->SetSpawnPos(_hpBarBase->GetPos());
	
	_hpBarGauge = make_shared<Object>(); 
	_hpBarGauge->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/HpBar_Gauge.png"));
	_hpBarGauge->GetTexture()->SetLeft(_hpBarEmpty->GetTexture()->Left() + 132);
	_hpBarGauge->GetPos().y = _hpBarEmpty->GetPos().y;
	_hpBarGauge->SetSpawnPos(_hpBarGauge->GetPos());

	_weaponSlot1 = make_shared<Object>();
	_weaponSlot1->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/WeaponSlot_1.png"));
	_weaponSlot1->GetTexture()->SetRight(WIN_WIDTH - 25);
	_weaponSlot1->GetTexture()->SetBottom(25);
	_weaponSlot1->SetSpawnPos(_weaponSlot1->GetPos());

	_weaponSlot2 = make_shared<Object>();
	_weaponSlot2->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/WeaponSlot_2.png"));
	_weaponSlot2->GetTexture()->SetRight(WIN_WIDTH - 10);
	_weaponSlot2->GetTexture()->SetBottom(40);
	_weaponSlot2->SetSpawnPos(_weaponSlot2->GetPos());

	_coinIcon = make_shared<Object>();
	_coinIcon->SetTexture(make_shared<Quad>(L"Resource/Icon/CoinIcon.png"));
	_coinIcon->GetTexture()->SetLeft(37);
	_coinIcon->GetTexture()->SetBottom(77);
	_coinIcon->SetSpawnPos(_coinIcon->GetPos());

	_hungryIcon = make_shared<Object>();
	_hungryIcon->SetTexture(make_shared<Quad>(L"Resource/Icon/HungryIcon.png"));
	_hungryIcon->GetTexture()->SetLeft(26);
	_hungryIcon->GetTexture()->SetBottom(33);
	_hungryIcon->SetSpawnPos(_hungryIcon->GetPos());
}

NomalUI::~NomalUI()
{
}

void NomalUI::Update()
{
	_cursur->GetTransform()->GetPos() = MOUSE_POS;
	_cursur->Update();

	_hpBarEmpty->Update();

	float hpRatio = 0.0f;
	if (GAME->GetPlayer() != nullptr)
		hpRatio = GAME->GetPlayer()->GetStatus().GetHpRatio();

	_hpBarGauge->SetPos(_hpBarGauge->GetSpawnPos());
	_hpBarGauge->GetTexture()->GetTransform()->GetScale().x = hpRatio;
	_hpBarGauge->GetTexture()->SetLeft(_hpBarGauge->GetPos().x - _hpBarGauge->GetTexture()->GetHalfSize().x);
	_hpBarGauge->Update();

	_hpBarBase->Update();

	if (INVENTORY->GetCurWeaponSlot() == 0)
	{
		_weaponSlot1->SetPos(_weaponSlot1->GetSpawnPos());
		_weaponSlot2->SetPos(_weaponSlot2->GetSpawnPos());
	}
	else
	{
		_weaponSlot1->SetPos(_weaponSlot2->GetSpawnPos());
		_weaponSlot2->SetPos(_weaponSlot1->GetSpawnPos());
	}
	_weaponSlot1->Update();

	_weaponSlot2->Update();

	_coinIcon->Update();

	_hungryIcon->Update();
}

void NomalUI::SetRTV()
{
}

void NomalUI::PostRender()
{
	_hpBarBase->Render();
	_hpBarGauge->Render();
	_hpBarEmpty->Render();

	if (INVENTORY->GetCurWeaponSlot() == 0)
	{
		_weaponSlot2->Render();
		_weaponSlot1->Render();
	}
	else
	{
		_weaponSlot1->Render();
		_weaponSlot2->Render();
	}
	shared_ptr<Quad> weaponImage = make_shared<Quad>(INVENTORY->GetCurWeapon()->GetTexture()->GetTextureFile());
	weaponImage->GetTransform()->GetPos() = _weaponSlot1->GetSpawnPos();
	switch (INVENTORY->GetCurWeapon()->GetWeaponType())
	{
	case Weapon::MELEE:
		weaponImage->GetTransform()->GetAngle() = (1.5f * PI);
		break;
	case Weapon::GUN:
		break;
	case Weapon::SUB:
		break;
	default:
		break;
	}

	weaponImage->Update();
	weaponImage->Render();

	_coinIcon->Render();
	_hungryIcon->Render();

	int maxHp = GAME->GetPlayer()->GetStatus()._hpMax;
	int hp = GAME->GetPlayer()->GetStatus()._hp;
	if (hp < 0)
		hp = 0;

	std::wstring hpText;
	hpText += to_wstring(hp);
	hpText += L" / ";
	hpText += to_wstring(maxHp);
	RECT hpTextRect =
	{
		_hpBarGauge->GetSpawnPos().x - (_hpBarTextSize * hpText.size() / 5),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) + _hpBarTextSize / 1.4,
		_hpBarGauge->GetSpawnPos().x + (_hpBarTextSize * hpText.size()),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) - _hpBarTextSize / 1.4
	};

	DirectWrite::GetInstance()->RenderText(hpText, hpTextRect, _hpBarTextSize);

	std::wstring levelText;
	levelText += to_wstring(INVENTORY->GetPlayerLevel());
	RECT levelTextRect =
	{
		(_hpBarGauge->GetSpawnPos().x - 215) - (_hpBarTextSize * levelText.size() / 5),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) + _hpBarTextSize / 1.4,
		(_hpBarGauge->GetSpawnPos().x - 215) + (_hpBarTextSize * levelText.size()),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) - _hpBarTextSize / 1.4
	};

	DirectWrite::GetInstance()->RenderText(levelText, levelTextRect, _hpBarTextSize);

	std::wstring goldText;
	goldText += to_wstring(INVENTORY->GetGold());
	RECT goldTextRect =
	{
		((_coinIcon->GetSpawnPos().x + _coinIcon->GetTexture()->GetHalfSize().x) + 26),										(WIN_HEIGHT - _coinIcon->GetSpawnPos().y) + _infoTextSize / 1.4,
		((_coinIcon->GetSpawnPos().x + _coinIcon->GetTexture()->GetHalfSize().x) + 26) + (_infoTextSize * goldText.size()),	(WIN_HEIGHT - _coinIcon->GetSpawnPos().y) - _infoTextSize / 1.4
	};

	DirectWrite::GetInstance()->RenderText(goldText, goldTextRect, _infoTextSize);

	std::wstring hungryText;
	hungryText += to_wstring(INVENTORY->GetCurHungry());
	hungryText += L" / ";
	hungryText += to_wstring(INVENTORY->GetHungryMax());
	RECT hungryTextRect =
	{
		((_hungryIcon->GetSpawnPos().x + _hungryIcon->GetTexture()->GetHalfSize().x) + 15),											(WIN_HEIGHT - _hungryIcon->GetSpawnPos().y) + _infoTextSize / 1.4,
		((_hungryIcon->GetSpawnPos().x + _hungryIcon->GetTexture()->GetHalfSize().x) + 15) + (_infoTextSize * hungryText.size()),	(WIN_HEIGHT - _hungryIcon->GetSpawnPos().y) - _infoTextSize / 1.4
	};

	DirectWrite::GetInstance()->RenderText(hungryText, hungryTextRect, _infoTextSize);

	_cursur->Render();
}
