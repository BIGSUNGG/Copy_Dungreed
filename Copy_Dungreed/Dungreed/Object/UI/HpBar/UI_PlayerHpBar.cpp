#include "framework.h"
#include "UI_PlayerHpBar.h"

UI_PlayerHpBar::UI_PlayerHpBar()
	: UI()
{
	_uiType = UI::HPBAR;

	_hpBarEmpty = make_shared<Object>();
	_hpBarEmpty->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Empty.png"));
	_hpBarEmpty->GetTexture()->SetLeft(18);
	_hpBarEmpty->GetTexture()->SetTop(WIN_HEIGHT - 18);
	_hpBarEmpty->SetSpawnPos(_hpBarEmpty->GetPos());

	_hpBarBase = make_shared<Object>();
	_hpBarBase->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Base.png"));
	_hpBarBase->GetTexture()->SetLeft(18);
	_hpBarBase->GetTexture()->SetTop(WIN_HEIGHT - 18);
	_hpBarBase->SetSpawnPos(_hpBarBase->GetPos());

	_hpBarGauge = make_shared<Object>();
	_hpBarGauge->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Gauge.png"));
	_hpBarGauge->GetTexture()->SetLeft(_hpBarEmpty->GetTexture()->Left() + 132);
	_hpBarGauge->GetPos().y = _hpBarEmpty->GetPos().y;
	_hpBarGauge->SetSpawnPos(_hpBarGauge->GetPos());
}

void UI_PlayerHpBar::Update()
{
	_hpBarEmpty->Update();

	float hpRatio = 0.0f;
	if (GAME->GetPlayer() != nullptr)
		hpRatio = GAME->GetPlayer()->GetStatus().GetHpRatio();

	_hpBarGauge->SetPos(_hpBarGauge->GetSpawnPos());
	_hpBarGauge->GetTexture()->GetTransform()->GetScale().x = hpRatio;
	_hpBarGauge->GetTexture()->SetLeft(_hpBarGauge->GetPos().x - _hpBarGauge->GetTexture()->GetHalfSize().x);
	_hpBarGauge->Update();

	_hpBarBase->Update();
}

void UI_PlayerHpBar::Render()
{
	_hpBarBase->Render();
	_hpBarGauge->Render();
	_hpBarEmpty->Render();

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
		_hpBarGauge->GetSpawnPos().x - (_hpBarTextSize * hpText.size() / 4),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) + _hpBarTextSize / 1.9,
		_hpBarGauge->GetSpawnPos().x + (_hpBarTextSize * hpText.size()),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) - _hpBarTextSize / 1.9
	};

	DirectWrite::GetInstance()->RenderText(hpText, hpTextRect, _hpBarTextSize);

	std::wstring levelText;
	levelText += to_wstring(INVENTORY->GetPlayerLevel());
	RECT levelTextRect =
	{
		(_hpBarGauge->GetSpawnPos().x - 215) - (_hpBarTextSize * levelText.size() / 4),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) + _hpBarTextSize / 1.9,
		(_hpBarGauge->GetSpawnPos().x - 215) + (_hpBarTextSize * levelText.size()),(WIN_HEIGHT - _hpBarGauge->GetSpawnPos().y) - _hpBarTextSize / 1.9
	};

	DirectWrite::GetInstance()->RenderText(levelText, levelTextRect, _hpBarTextSize);
}
