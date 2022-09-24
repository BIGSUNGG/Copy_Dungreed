#include "framework.h"
#include "NomalUI.h"

NomalUI::NomalUI()
{
	_uiType = UI::NOMAL;

	auto object = make_shared<Object>();
	object->SetTexture(make_shared<Quad>(L"Resource/Ui/Nomal/HpBar_Full.png"));
	object->GetTexture()->SetLeft(25);
	object->GetTexture()->SetTop(WIN_HEIGHT - 25);
	object->SetSpawnPos(object->GetPos());
	_objects.emplace_back(object);
}

NomalUI::~NomalUI()
{
}
