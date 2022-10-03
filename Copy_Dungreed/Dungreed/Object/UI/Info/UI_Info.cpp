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
	RECT goldTextRect =
	{
		((_coinIcon->GetTransform()->GetPos().x + _coinIcon->GetHalfSize().x) + 26),										(WIN_HEIGHT - _coinIcon->GetTransform()->GetPos().y) + _infoTextSize / 1.9,
		((_coinIcon->GetTransform()->GetPos().x + _coinIcon->GetHalfSize().x) + 26) + (_infoTextSize * goldText.size()),	(WIN_HEIGHT - _coinIcon->GetTransform()->GetPos().y) - _infoTextSize / 1.9
	};

	DirectWrite::GetInstance()->RenderText(goldText, goldTextRect, _infoTextSize);

	std::wstring hungryText;
	hungryText += to_wstring(INVENTORY->GetCurHungry());
	hungryText += L" / ";
	hungryText += to_wstring(INVENTORY->GetHungryMax());
	RECT hungryTextRect =
	{
		((_hungryIcon->GetTransform()->GetPos().x + _hungryIcon->GetHalfSize().x) + 15),											(WIN_HEIGHT - _hungryIcon->GetTransform()->GetPos().y) + _infoTextSize / 1.9,
		((_hungryIcon->GetTransform()->GetPos().x + _hungryIcon->GetHalfSize().x) + 15) + (_infoTextSize * hungryText.size()),	(WIN_HEIGHT - _hungryIcon->GetTransform()->GetPos().y) - _infoTextSize / 1.9
	};

	DirectWrite::GetInstance()->RenderText(hungryText, hungryTextRect, _infoTextSize);
}
