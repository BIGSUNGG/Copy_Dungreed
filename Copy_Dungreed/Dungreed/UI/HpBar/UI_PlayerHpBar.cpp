#include "framework.h"
#include "UI_PlayerHpBar.h"

UI_PlayerHpBar::UI_PlayerHpBar()
	: UI()
{
	_uiType = UI::HPBAR;

	_hpBarEmpty = make_shared<Object>();
	_hpBarEmpty->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Empty.png"));
	_hpBarEmpty->GetObjectTexture()->SetLeft(18);
	_hpBarEmpty->GetObjectTexture()->SetTop(WIN_HEIGHT - 18);
	_hpBarEmpty->SetSpawnPos(_hpBarEmpty->GetPos());

	_hpBarBase = make_shared<Object>();
	_hpBarBase->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Base.png"));
	_hpBarBase->GetObjectTexture()->SetLeft(18);
	_hpBarBase->GetObjectTexture()->SetTop(WIN_HEIGHT - 18);
	_hpBarBase->SetSpawnPos(_hpBarBase->GetPos());

	_hpBarGauge = make_shared<Object>();
	_hpBarGauge->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/HpBar_Gauge.png"));
	_hpBarGauge->GetObjectTexture()->SetLeft(_hpBarEmpty->GetObjectTexture()->Left() + 132);
	_hpBarGauge->GetPos().y = _hpBarEmpty->GetPos().y;
	_hpBarGauge->SetSpawnPos(_hpBarGauge->GetPos());

	_dashBarGaugeBaseLeft = make_shared<Object>();
	_dashBarGaugeBaseLeft->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/Dash_Left_Base.png"));
	_dashBarGaugeBaseLeft->GetObjectTexture()->SetLeft(18);
	_dashBarGaugeBaseLeft->GetPos().y = WIN_HEIGHT - 150;
	_dashBarGaugeBaseLeft->SetSpawnPos(_dashBarGaugeBaseLeft->GetPos());

	_dashBarGaugeBaseMid = make_shared<Object>();
	_dashBarGaugeBaseMid->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/Dash_Mid_Base.png"));
	_dashBarGaugeBaseMid->GetObjectTexture()->SetLeft(_dashBarGaugeBaseLeft->GetObjectTexture()->Right());
	_dashBarGaugeBaseMid->GetPos().y = WIN_HEIGHT - 150;
	_dashBarGaugeBaseMid->SetSpawnPos(_dashBarGaugeBaseMid->GetPos());

	_dashBarGaugeBaseRight = make_shared<Object>();
	_dashBarGaugeBaseRight->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/Dash_Right_Base.png"));
	_dashBarGaugeBaseRight->GetObjectTexture()->SetLeft(_dashBarGaugeBaseMid->GetObjectTexture()->Right());
	_dashBarGaugeBaseRight->GetPos().y = WIN_HEIGHT - 150;
	_dashBarGaugeBaseRight->SetSpawnPos(_dashBarGaugeBaseRight->GetPos());

	_dashBarGaugeLeft = make_shared<Object>();
	_dashBarGaugeLeft->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/Dash_Left_Full.png"));
	_dashBarGaugeLeft->GetObjectTexture()->SetLeft(18);
	_dashBarGaugeLeft->GetPos().y = WIN_HEIGHT - 150;
	_dashBarGaugeLeft->SetSpawnPos(_dashBarGaugeLeft->GetPos());

	_dashBarGaugeMid = make_shared<Object>();
	_dashBarGaugeMid->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/Dash_Mid_Full.png"));
	_dashBarGaugeMid->GetObjectTexture()->SetLeft(_dashBarGaugeBaseLeft->GetObjectTexture()->Right());
	_dashBarGaugeMid->GetPos().y = WIN_HEIGHT - 150;
	_dashBarGaugeMid->SetSpawnPos(_dashBarGaugeMid->GetPos());

	_dashBarGaugeRight = make_shared<Object>();
	_dashBarGaugeRight->SetTexture(make_shared<Quad>(L"Resource/Ui/HpBar/Dash_Right_Full.png"));
	_dashBarGaugeRight->GetObjectTexture()->SetLeft(_dashBarGaugeBaseMid->GetObjectTexture()->Right());
	_dashBarGaugeRight->GetPos().y = WIN_HEIGHT - 150;
	_dashBarGaugeRight->SetSpawnPos(_dashBarGaugeRight->GetPos());
	
	_hpText = make_shared<UI_Text>();
	_hpText->SetPos(_hpBarGauge->GetSpawnPos());
	_hpText->SetTextStatus(UI_Text::Text_Status::MID);
	_hpText->SetTextSize(65);

	_levelText = make_shared<UI_Text>();
	_levelText->SetPos(Vector2(_hpBarGauge->GetSpawnPos().x - 215 , _hpBarGauge->GetSpawnPos().y));
	_levelText->SetTextStatus(UI_Text::Text_Status::MID);
	_levelText->SetTextSize(65);
}

void UI_PlayerHpBar::Update()
{
	_hpBarEmpty->Update();

	float hpRatio = 0.0f;
	if (GAME->GetPlayer() != nullptr)
		hpRatio = GAME->GetPlayer()->GetStatus().GetHpRatio();

	_hpBarGauge->SetPos(_hpBarGauge->GetSpawnPos());
	_hpBarGauge->GetObjectTexture()->GetTransform()->GetScale().x = hpRatio;
	_hpBarGauge->GetObjectTexture()->SetLeft(_hpBarGauge->GetPos().x - _hpBarGauge->GetObjectTexture()->GetHalfSize().x);
	_hpBarGauge->Update();

	_hpBarBase->Update();

	_dashBarGaugeBaseLeft->Update();
	_dashBarGaugeBaseMid->Update();
	_dashBarGaugeBaseRight->Update();

	const int& dashCount = GAME->GetPlayer()->GetDashInfo()._dashCount;

	if (dashCount > 2)
	{
		_dashBarGaugeLeft->GetRender() = true;
		_dashBarGaugeMid->GetRender() = true;
		_dashBarGaugeRight->GetRender() = true;
	}
	else if (dashCount > 1)
	{
		_dashBarGaugeLeft->GetRender() = true;
		_dashBarGaugeMid->GetRender() = true;
		_dashBarGaugeRight->GetRender() = false;
	}
	else if (dashCount > 0)
	{
		_dashBarGaugeLeft->GetRender() = true;
		_dashBarGaugeMid->GetRender() = false;
		_dashBarGaugeRight->GetRender() = false;
	}
	else
	{
		_dashBarGaugeLeft->GetRender() = false;
		_dashBarGaugeMid->GetRender() = false;
		_dashBarGaugeRight->GetRender() = false;
	}

	_dashBarGaugeLeft->Update();
	_dashBarGaugeMid->Update();
	_dashBarGaugeRight->Update();
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
	wstring curHpText = to_wstring(hp);
	wstring maxHpText = to_wstring(maxHp);

	for (int i = 0; i <maxHpText.length() - curHpText.length(); i++)
	{
		hpText += L" ";
	}

	hpText += curHpText;
	hpText += L" / ";
	hpText += maxHpText;
	_hpText->SetText(hpText);
	_hpText->Render();

	std::wstring levelText;
	levelText += to_wstring(INVENTORY->GetPlayerLevel());
	_levelText->SetText(levelText);
	_levelText->Render();

	_dashBarGaugeBaseLeft->Render();
	_dashBarGaugeBaseMid->Render();
	_dashBarGaugeBaseRight->Render();

	_dashBarGaugeLeft->Render();
	_dashBarGaugeMid->Render();
	_dashBarGaugeRight->Render();
}
