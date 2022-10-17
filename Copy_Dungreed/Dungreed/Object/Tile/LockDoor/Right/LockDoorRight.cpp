#include "framework.h"
#include "LockDoorRight.h"

LockDoorRight::LockDoorRight()
	: LockDoor()
{
	_moveDirection = { 1,0 };

	SetAnimation();
	GetAnimation()->_animSpeed[LockDoor::LOCK] = vector<float>(8, 0.1f);
	GetAnimation()->_animState[LockDoor::LOCK] = Animation::Anim_State::END;
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Lock/Stele00.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Lock/Stele01.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Lock/Stele02.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Lock/Stele03.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Lock/Stele04.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Lock/Stele05.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Lock/Stele06.png");
	GetAnimation()->_animList[LockDoor::LOCK].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Lock/Stele07.png");

	GetAnimation()->_animSpeed[LockDoor::IDLE] = vector<float>(8, 0.05f);
	GetAnimation()->_animState[LockDoor::IDLE] = Animation::Anim_State::LOOP;
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Idle/Stele08.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Idle/Stele09.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Idle/Stele10.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Idle/Stele11.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Idle/Stele12.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Idle/Stele13.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Idle/Stele14.png");
	GetAnimation()->_animList[LockDoor::IDLE].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Idle/Stele15.png");

	GetAnimation()->_animSpeed[LockDoor::OPEN] = vector<float>(8, 0.1f);
	GetAnimation()->_animState[LockDoor::OPEN] = Animation::Anim_State::END;
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Open/Stele16.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Open/Stele17.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Open/Stele18.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Open/Stele19.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Open/Stele20.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Open/Stele21.png");
	GetAnimation()->_animList[LockDoor::OPEN].push_back(L"Resource/Map/Public/Lock/LockDoorRight/Open/Stele22.png");

	auto texture = make_shared<Quad>(GetAnimation()->_animList[LockDoor::LOCK][0]);
	SetTexture(texture);

	GetAnimation()->SetTexture(texture);
}

void LockDoorRight::DoorOpenEffect()
{
	auto trail = make_shared<Effect_Trail>();
	auto quad = make_shared<Quad>(L"Resource/Effect/LockDoor/DoorEffect.png");
	trail->SetTexture(quad);
	trail->GetPos().x = MathUtility::RandomFloat(MAP_MANAGER->GetCurMap()->GetRightDoor().x - _texture->GetHalfSize().x, MAP_MANAGER->GetCurMap()->GetRightDoor().x + _texture->GetHalfSize().x);
	trail->GetPos().y = MathUtility::RandomFloat(MAP_MANAGER->GetCurMap()->GetRightDoor().y - (_texture->GetHalfSize().y * 0.7), MAP_MANAGER->GetCurMap()->GetRightDoor().y + (_texture->GetHalfSize().y * 0.7));
	trail->SetAlpha(MathUtility::RandomFloat(0.3f, 0.7f));
	trail->GetObjectTexture()->GetTransform()->GetScale() *= MathUtility::RandomFloat(0.5f, 1.0f);
	trail->SetFadeRatio(0.7f);
	trail->SetDirection({ -1,0 });
	trail->SetSpeed(100.0f);
	GAME->AddEffect(trail);
}
