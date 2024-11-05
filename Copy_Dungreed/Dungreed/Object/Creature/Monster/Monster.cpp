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

	// �÷��̾�� �� ������Ʈ�� �Ÿ��� Ž�� �Ÿ��ȿ� �ִٸ�
	float length = (_texture->GetTransform()->GetPos() - GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos()).Length();
	if (length <= _searchLength)
	{
		// Ÿ�� ����
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

	// ������ �Ҹ� ����
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
	// ���� ����Ʈ ����
	shared_ptr<Effect> spawn = MAKE_CREATURE_EFFECT(StageMap::Level::PUBLIC, 1);
	spawn->GetObjectTexture()->GetTransform()->GetPos() = _texture->GetTransform()->GetPos();

	// Ư�� �ִϸ��̼� �κп��� ȣ��� �Լ� ����
	function<void(pair<int, int> pair)> func = [&](pair<int, int> pair) {		
		if (pair.first == BASIC && pair.second == 10)
		{
			// ������Ʈ ��ȯ
			_render = true;
			_spawn = true;
		}
		if (pair.first == BASIC && pair.second == 14)
		{
			// AI ����
			_enableAI = true;
		}
	};
	spawn->GetAnimation()->SetAfterChangeFunc(func);

	GAME->AddEffect(spawn);
}
