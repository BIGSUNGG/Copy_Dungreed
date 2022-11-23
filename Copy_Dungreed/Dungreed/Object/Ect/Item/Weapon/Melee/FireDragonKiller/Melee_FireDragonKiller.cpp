#include "framework.h"
#include "Melee_FireDragonKiller.h"

Melee_FireDragonKiller::Melee_FireDragonKiller(int level, int num)
	: Melee(level, num)
{
	_fireEffectAnim.emplace_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/BurnFX0.png");
	_fireEffectAnim.emplace_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/BurnFX1.png");
	_fireEffectAnim.emplace_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/BurnFX2.png");
	_fireEffectAnim.emplace_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/BurnFX3.png");
	_fireEffectAnim.emplace_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/BurnFX4.png");
	_fireEffectAnim.emplace_back(L"Resource/Effect/Weapon/Melee/FireDrangonKiller/BurnFX5.png");

	_fireEffect.resize(10);
}

void Melee_FireDragonKiller::Update()
{
	Melee::Update();

	_effectRunTime += DELTA_TIME;
	if (_effectRunTime >= _effectDelay)
	{
		_effectRunTime = 0.0f;
		FireEffect();
	}

	for (auto effect : _fireEffect)
	{
		if (effect == nullptr || !effect->IsActive())
			continue;

		effect->Update();
	}
}

void Melee_FireDragonKiller::Render()
{
	Melee::Render();
	
	for (auto effect : _fireEffect)
	{
		if (effect == nullptr || !effect->IsActive())
			continue;

		effect->Render();
	}
}

void Melee_FireDragonKiller::FireEffect()
{
	shared_ptr<Effect> effect = make_shared<Effect>(0, 0);
	effect->SetAnimation();
	effect->GetAnimation()->_animSpeed[BASIC] = vector<float>(6, 0.1f);
	effect->GetAnimation()->_animState[BASIC] = Animation::Anim_State::END;
	effect->GetAnimation()->_animList[BASIC] = _fireEffectAnim;
	effect->SetTexture(make_shared<Quad>(effect->GetAnimation()->_animList[BASIC][BASIC]));
	effect->GetAnimation()->SetTexture(effect->GetObjectTexture());

	float angle = _springArm->GetAngle() / PI;
	Vector2 direction = { 1.0f,tan(_springArm->GetAngle()) };

	if (angle > 0.5f || angle < -0.5f)
		direction *= -1;

	direction.Normalize();
	float length = direction.x * _texture->GetHalfSize().y;
	float height = direction.y * _texture->GetHalfSize().x;
	if (height > 0)
		height += 15.f;
	else
		height -= 15.f;

	Vector2 pos = {
		MathUtility::RandomFloat(-height,height),
		MathUtility::RandomFloat(-length,length),
	};

	effect->SetPos(_texture->GetTransform()->GetWorldPos() + pos);
	_fireEffect.emplace_back(effect);
}
