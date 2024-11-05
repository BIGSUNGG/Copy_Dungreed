#include "framework.h"
#include "Monster.h"

Monster::Monster(int level, int num)
	:Creature(level, num)
{
	_creatureType = Creature_Type::ENEMY;
	_damagedDuration = 0.05f;
	_render = false;
	
	SOUND->Add("Hit_Monster", "Resource/Sound/Creature/Monster/Hit/Hit_Monster.wav");
	SOUND->Add("MonsterDie", "Resource/Sound/Creature/Monster/Die/MonsterDie.wav");
}

void Monster::Update()
{
	if (GAME->GetPlaying())
	{
		if (_spawn == false)
			SearchTarget();

		if (_enableAI == true && _target.lock() != nullptr)
			AI();
	}

	if (_render == true)
		Creature::Update();
	else
		Object::Update();
}

void Monster::Render()
{
	bool temp = GAME->GetPlaying();
	if (_render || (GAME->GetPlaying() == false || GAME->GetPlayer() == nullptr))
		Creature::Render();
}

void Monster::SearchTarget()
{
	if (_target.lock() != nullptr)
		return;

	// 플레이어와 이 오브젝트의 거리가 탐색 거리안에 있다면
	float length = (_texture->GetTransform()->GetPos() - GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos()).Length();
	if (length <= _searchLength)
	{
		// 타겟 설정
		SetTarget(GAME->GetPlayer());
		MAP_MANAGER->SetTarget(GAME->GetPlayer());
	}
}

void Monster::AI()
{
}

void Monster::SetTarget(shared_ptr<Creature> target)
{
	_target = target;
	SpawnEffect();
}

float Monster::TakeDamage(float baseDamage, shared_ptr<Creature> attacker)
{
	if(_spawn == false)
		return false;

	const float& damaged = Creature::TakeDamage(baseDamage, attacker);

	// 데미지 소리 생성
	if (_status._hp > 0)
	{
		SOUND->Play("Hit_Monster");
		_buffer->_data.selected = 1;
		_buffer->_data.value1 = 1;
		_buffer->_data.value2 = 0;
		_buffer->_data.value3 = 0;
	}
	else
		SOUND->Play("MonsterDie");

	return damaged;
}

void Monster::SpawnEffect()
{
	// 스폰 이펙트 생성
	shared_ptr<Effect> spawn = MAKE_CREATURE_EFFECT(StageMap::Level::PUBLIC, 1);
	spawn->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

	// 특정 애니메이션 부분에서 호출될 함수 설정
	function<void(pair<int, int> pair)> func = [&](pair<int, int> pair) {		
		if (pair.first == BASIC && pair.second == 10)
		{
			// 오브젝트 소환
			_render = true;
			_spawn = true;
		}
		if (pair.first == BASIC && pair.second == 14)
		{
			// AI 시작
			_enableAI = true;
		}
	};
	spawn->GetAnimation()->SetAfterChangeFunc(func);

	GAME->AddEffect(spawn);
}
