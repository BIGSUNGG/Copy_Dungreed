#include "framework.h"
#include "NomalUI.h"

NomalUI::NomalUI()
{
	_uiType = UI::GROUND;

	_hpBarEmpty = make_shared<Object>();
	_hpBarEmpty->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/HpBar_Empty.png"));
	_hpBarEmpty->GetTexture()->SetLeft(25);
	_hpBarEmpty->GetTexture()->SetTop(WIN_HEIGHT - 25);
	_hpBarEmpty->SetSpawnPos(_hpBarEmpty->GetPos());

	_hpBarBase = make_shared<Object>();
	_hpBarBase->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/HpBar_Base.png"));
	_hpBarBase->GetTexture()->SetLeft(25);
	_hpBarBase->GetTexture()->SetTop(WIN_HEIGHT - 25);
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

	_goldIcon = make_shared<Object>();
	_goldIcon->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/WeaponSlot_2.png"));
	_goldIcon->GetTexture()->SetRight(25);
	_goldIcon->GetTexture()->SetBottom(80);
	_goldIcon->SetSpawnPos(_goldIcon->GetPos());
}

NomalUI::~NomalUI()
{
}

void NomalUI::Update()
{
	_hpBarEmpty->SetPos(CAMERA->GetPos() + _hpBarEmpty->GetSpawnPos());
	_hpBarEmpty->Update();

	float hpRatio = 0.0f;
	if (GAME->GetPlayer() != nullptr)
		hpRatio = GAME->GetPlayer()->GetStatus().GetHpRatio();

	_hpBarGauge->SetPos(CAMERA->GetPos() + _hpBarGauge->GetSpawnPos());
	_hpBarGauge->GetTexture()->GetTransform()->GetScale().x = hpRatio;
	_hpBarGauge->GetTexture()->SetLeft(_hpBarGauge->GetPos().x - _hpBarGauge->GetTexture()->GetHalfSize().x);
	_hpBarGauge->Update();

	_hpBarBase->SetPos(CAMERA->GetPos() + _hpBarBase->GetSpawnPos());
	_hpBarBase->Update();

	if (INVENTORY->GetCurWeaponSlot() == 0)
	{
		_weaponSlot1->SetPos(CAMERA->GetPos() + _weaponSlot1->GetSpawnPos());
		_weaponSlot2->SetPos(CAMERA->GetPos() + _weaponSlot2->GetSpawnPos());
	}
	else
	{
		_weaponSlot1->SetPos(CAMERA->GetPos() + _weaponSlot2->GetSpawnPos());
		_weaponSlot2->SetPos(CAMERA->GetPos() + _weaponSlot1->GetSpawnPos());
	}
	_weaponSlot1->Update();

	_weaponSlot2->Update();
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
	weaponImage->GetTransform()->GetPos() = CAMERA->GetPos() + _weaponSlot1->GetSpawnPos();
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
		_hpBarGauge->GetSpawnPos().x - (_textSize * hpText.size() / 4.5),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) + _textSize / 1.4,
		_hpBarGauge->GetSpawnPos().x + (_textSize * hpText.size() / 4.5),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) - _textSize / 1.4
	};

	DirectWrite::GetInstance()->RenderText(hpText, hpTextRect, _textSize);

	std::wstring levelText;
	levelText += to_wstring(INVENTORY->GetPlayerLevel());
	RECT levelTextRect =
	{
		(_hpBarGauge->GetSpawnPos().x - 210) - (_textSize * levelText.size() / 4.5),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) + _textSize / 1.4,
		(_hpBarGauge->GetSpawnPos().x - 210) + (_textSize * levelText.size() / 4.5),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) - _textSize / 1.4
	};

	DirectWrite::GetInstance()->RenderText(levelText, levelTextRect, _textSize);
}
