#include "framework.h"
#include "NomalUI.h"

NomalUI::NomalUI()
{
	_uiType = UI::NOMAL;

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

	_hpBarGauge = make_shared<InstanceQuads>(L"Resource/Ui/Nomal/HpBar_Gauge.png", _hpBarGaugeSize);
	for (int i = 0; i < _hpBarGaugeSize; i++)
	{
		_hpBarGauge->GetTransforms()[i]->GetPos().x = _hpBarEmpty->GetTexture()->Left() + 133 + i;
		_hpBarGauge->GetTransforms()[i]->GetPos().y = _hpBarBase->GetPos().y;
	}
	_hpBarGauge->ApplyChanges();
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

	_hpBarGauge->SetRenderPercent(hpRatio);
	for (int i = 0; i < _hpBarGaugeSize; i++)
	{
		_hpBarGauge->GetTransforms()[i]->GetPos().x = _hpBarEmpty->GetTexture()->Left() + 133 + i;
		_hpBarGauge->GetTransforms()[i]->GetPos().y = _hpBarBase->GetPos().y;
	}
	_hpBarGauge->ApplyChanges();

	_hpBarBase->SetPos(CAMERA->GetPos() + _hpBarBase->GetSpawnPos());
	_hpBarBase->Update();
}

void NomalUI::PostRender()
{
	_hpBarBase->Render();
	_hpBarGauge->Render();
	_hpBarEmpty->Render();
}
