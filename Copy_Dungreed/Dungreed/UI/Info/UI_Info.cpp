#include "framework.h"
#include "UI_Info.h"

UI_Info::UI_Info()
	: UI()
{
	_goldIcon = make_shared<Quad>(L"Resource/Icon/CoinIcon.png");
	_goldIcon->SetLeft(37);
	_goldIcon->SetBottom(77);
	_goldIcon->Update();

	_hungryIcon = make_shared<Quad>(L"Resource/Icon/HungryIcon.png");
	_hungryIcon->SetLeft(26);
	_hungryIcon->SetBottom(33);
	_hungryIcon->Update();

	_goldText = make_shared<UI_Text>();
	_goldText->SetPos(Vector2(_goldIcon->GetTransform()->GetPos().x + 40, _goldIcon->GetTransform()->GetPos().y));
	_goldText->SetTextSize(40);

	_hungryText = make_shared<UI_Text>();
	_hungryText->SetPos(Vector2(_hungryIcon->GetTransform()->GetPos().x + 40, _hungryIcon->GetTransform()->GetPos().y));
	_hungryText->SetTextSize(40);

	_hungryBase = make_shared<Quad>(L"Resource/Ui/Info/Hungry_Base.png");
	_hungryBase->GetTransform()->GetPos() = Vector2(150, 18);
	_hungryBase->Update();

	_hungryGauge = make_shared<Quad>(L"Resource/Ui/Info/Hungry_Gauge.png");
	_hungryGauge->GetTransform()->GetPos() = _hungryBase->GetTransform()->GetPos();
	_hungryGauge->Update();
}

void UI_Info::Update()
{

	std::wstring goldText;
	goldText += to_wstring(INVENTORY->GetCurGold());

	_goldText->SetText(goldText);

	std::wstring hungryText;
	hungryText += to_wstring(INVENTORY->GetCurHungry());
	hungryText += L"/";
	hungryText += to_wstring(INVENTORY->GetHungryMax());

	_hungryText->SetText(hungryText);

	// 허기 게이지 설정
	_hungryGauge->GetTransform()->GetScale().x = (float)INVENTORY->GetCurHungry() / (float)INVENTORY->GetHungryMax();
	_hungryGauge->SetLeft(_hungryBase->Left() + 3);
	_hungryGauge->Update();
}

void UI_Info::Render()
{
	_goldIcon->Render();
	_hungryIcon->Render();

	_goldText->Render();
	_hungryText->Render();

	_hungryBase->Render();
	_hungryGauge->Render();
}
