#include "framework.h"
#include "UI_Info.h"

UI_Info::UI_Info()
{
	_uiType = UI::INFO;

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
}
