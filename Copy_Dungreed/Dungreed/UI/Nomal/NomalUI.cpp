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

	_hpBarGauge.reserve(_hpBarGaugeSize);
	for (int i = 0; i < _hpBarGaugeSize; i++)
	{
		auto bar = make_shared<Object>();
		bar->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/HpBar_Gauge.png"));
		bar->GetTexture()->GetTransform()->GetPos().x = _hpBarEmpty->GetTexture()->Left() + 133 + i;
		bar->GetTexture()->GetTransform()->GetPos().y = _hpBarBase->GetPos().y;
		bar->SetSpawnPos(bar->GetPos());
		_hpBarGauge.emplace_back(bar);
	}
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

	for (int i = 0; i < _hpBarGaugeSize; i++)
	{
		
		if ((float)i / (float)_hpBarGaugeSize < hpRatio)
		{
			_hpBarGauge[i]->SetPos(CAMERA->GetPos() + _hpBarGauge[i]->GetSpawnPos());
			_hpBarGauge[i]->GetRender() = true;
			_hpBarGauge[i]->Update();
		}
		else
			_hpBarGauge[i]->GetRender() = false;
	}

	_hpBarBase->SetPos(CAMERA->GetPos() + _hpBarBase->GetSpawnPos());
	_hpBarBase->Update();
}

void NomalUI::PostRender()
{
	_hpBarBase->Render();
	for (auto& bar : _hpBarGauge)
		bar->Render();
	_hpBarEmpty->Render();
}
