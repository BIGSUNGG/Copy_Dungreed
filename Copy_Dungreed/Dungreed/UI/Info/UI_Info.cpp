#include "framework.h"
#include "UI_Info.h"

UI_Info::UI_Info()
	: UI()
{
	_uiType = UI::INFO;

	_coinIcon = make_shared<Quad>(L"Resource/Icon/CoinIcon.png");
	_coinIcon->SetLeft(37);
	_coinIcon->SetBottom(77);

	_hungryIcon = make_shared<Quad>(L"Resource/Icon/HungryIcon.png");
	_hungryIcon->SetLeft(26);
	_hungryIcon->SetBottom(33);

	_coinText = make_shared<UI_Text>();
	_coinText->SetPos(Vector2(_coinIcon->GetTransform()->GetPos().x + 35, _coinIcon->GetTransform()->GetPos().y));
	_coinText->SetTextSize(35);

	_hungryText = make_shared<UI_Text>();
	_hungryText->SetPos(Vector2(_hungryIcon->GetTransform()->GetPos().x + 35, _hungryIcon->GetTransform()->GetPos().y));
	_hungryText->SetTextSize(35);
}

void UI_Info::Update()
{
	_coinIcon->Update();
	_hungryIcon->Update();

}

void UI_Info::Render()
{
	_coinIcon->Render();
	_hungryIcon->Render();

	std::wstring goldText;
	goldText += to_wstring(INVENTORY->GetGold());

	_coinText->SetText(goldText);
	_coinText->Render();

	std::wstring hungryText;
	hungryText += to_wstring(INVENTORY->GetCurHungry());
	hungryText += L" / ";
	hungryText += to_wstring(INVENTORY->GetHungryMax());

	_hungryText->SetText(hungryText);
	_hungryText->Render();
}
