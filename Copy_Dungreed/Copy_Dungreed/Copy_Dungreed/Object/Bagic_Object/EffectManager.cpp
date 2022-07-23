#include "framework.h"
#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Add(wstring file, Vector2 maxFrame, UINT poolCount , float speed, Action::Type type)
{
	string effectName = WstrToStr(file);
	size_t t = effectName.find("Effects/");
	effectName = effectName.substr(t + 8, effectName.length());
	effectName = effectName.substr(0, effectName.length() - 4);

	if (_effects.count(effectName) > 0)
		return;

	vector<shared_ptr<Effect>> v;
	v.reserve(poolCount);
	for (int i = 0; i < poolCount; i++)
	{
		shared_ptr<Effect> effect = make_shared<Effect>(file, maxFrame, speed, type);
		effect->_isActive = false;
		v.emplace_back(effect);
	}

	_effects[effectName] = v;
}

void EffectManager::Play(string name, Vector2 pos)
{
	if (_effects.count(name) == 0)
		return;

	for (auto& effect : _effects[name])
	{
		if (effect->_isActive == false)
		{
			effect->Play(pos);
			return;
		}
	}
}

void EffectManager::Update()
{
	for (auto& pair : _effects)
	{
		for (auto& effect : pair.second)
		{
			effect->Update();
		}
	}
}

void EffectManager::Render()
{
	for (auto& pair : _effects)
	{
		for (auto& effect : pair.second)
		{
			effect->Render();
		}
	}
}

