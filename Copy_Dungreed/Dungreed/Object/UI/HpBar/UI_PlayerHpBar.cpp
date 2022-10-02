#include "framework.h"
#include "UI_PlayerHpBar.h"

UI_PlayerHpBar::UI_PlayerHpBar()
{
	_uiType = UI::HPBAR;

	_hpBarEmpty = make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Empty.png");
	_hpBarEmpty->SetLeft(18);
	_hpBarEmpty->SetTop(WIN_HEIGHT - 18);

	_hpBarBase = make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Base.png");
	_hpBarBase->SetLeft(18);
	_hpBarBase->SetTop(WIN_HEIGHT - 18);

	_hpBarGauge = make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Gauge.png");
	_hpBarGauge->SetLeft(_hpBarEmpty->Left() + 132);
	_hpBarGauge->GetTransform()->GetPos().y = _hpBarEmpty->GetTransform()->GetPos().y;
}

void UI_PlayerHpBar::Update()
{
	_hpBarEmpty->Update();

	float hpRatio = 0.0f;
	if (GAME->GetPlayer() != nullptr)
		hpRatio = GAME->GetPlayer()->GetStatus().GetHpRatio();

	_hpBarGauge->GetTransform()->GetScale().x = hpRatio;
	_hpBarGauge->SetLeft(_hpBarGauge->GetTransform()->GetPos().x - _hpBarGauge->GetHalfSize().x);
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
		_hpBarGauge->GetTransform()->GetPos().x - (_hpBarTextSize * hpText.size() / 4),(WIN_HEIGHT - _hpBarGauge->GetTransform()->GetPos().y) + _hpBarTextSize / 1.9,
		_hpBarGauge->GetTransform()->GetPos().x + (_hpBarTextSize * hpText.size()),(WIN_HEIGHT - _hpBarGauge->GetTransform()->GetPos().y) - _hpBarTextSize / 1.9
	};

	DirectWrite::GetInstance()->RenderText(hpText, hpTextRect, _hpBarTextSize);

	std::wstring levelText;
	levelText += to_wstring(INVENTORY->GetPlayerLevel());
	RECT levelTextRect =
	{
		(_hpBarGauge->GetTransform()->GetPos().x - 215) - (_hpBarTextSize * levelText.size() / 5),(WIN_HEIGHT - _hpBarGauge->GetTransform()->GetPos().y) + _hpBarTextSize / 1.9,
		(_hpBarGauge->GetTransform()->GetPos().x - 215) + (_hpBarTextSize * levelText.size()),(WIN_HEIGHT - _hpBarGauge->GetTransform()->GetPos().y) - _hpBarTextSize / 1.9
	};

	DirectWrite::GetInstance()->RenderText(levelText, levelTextRect, _hpBarTextSize);
}
