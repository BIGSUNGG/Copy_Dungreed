#include "framework.h"
#include "UI_EnemyHpBar.h"

UI_EnemyHpBar::UI_EnemyHpBar()
{
}

void UI_EnemyHpBar::Update()
{
	auto& creatures = MAP_MANAGER->GetCurMap()->GetObjects()[Object::CREATURE];
	for (int i = 0; i < _hpBarBase.size(); i++)
	{
		if (creatures[i] != nullptr && creatures[i]->GetRender())
		{
			auto creature = dynamic_pointer_cast<Creature>(creatures[i]);
			float hpRatio = 0.0f;
			hpRatio = creature->GetStatus().GetHpRatio();

			if (creature->GetCreatureType() == Creature::ENEMY && hpRatio < 1.0f)
			{
				_hpBarBase[i]->GetRender() = true;
				_hpBarGauge[i]->GetRender() = true;

				_hpBarBase[i]->GetTexture()->SetTop(creature->GetTexture()->Bottom() - CAMERA->GetPos().y - 10.0f);
				_hpBarBase[i]->GetPos().x = creature->GetPos().x - CAMERA->GetPos().x;

				_hpBarGauge[i]->GetPos() = _hpBarBase[i]->GetPos();

				_hpBarGauge[i]->GetTexture()->GetTransform()->GetScale().x = hpRatio;
				_hpBarGauge[i]->GetTexture()->SetLeft(_hpBarGauge[i]->GetPos().x - _hpBarGauge[i]->GetTexture()->GetHalfSize().x);
				
			}
			else
			{
				_hpBarBase[i]->GetRender() = false;
				_hpBarGauge[i]->GetRender() = false;
			}
		}
		else
		{
			_hpBarBase[i]->GetRender() = false;
			_hpBarGauge[i]->GetRender() = false;
		}
		
		_hpBarBase[i]->Update();
		_hpBarGauge[i]->Update();
	}
}

void UI_EnemyHpBar::Render()
{
	for (int i = 0; i < _hpBarBase.size(); i++)
	{
		_hpBarBase[i]->Render();
		_hpBarGauge[i]->Render();
	}
}

void UI_EnemyHpBar::Refresh()
{
	_hpBarBase.clear();
	_hpBarGauge.clear();

	auto& creatures  = MAP_MANAGER->GetCurMap()->GetObjects()[Object::CREATURE];
	_hpBarBase.resize(creatures.size());
	_hpBarGauge.resize(creatures.size());

	for (int i = 0; i < _hpBarBase.size(); i++)
	{
		_hpBarBase[i] = make_shared<Object>();
		auto hpBarBaseQuad = make_shared<Quad>(L"Resource/Ui/HpBar/Enemy_HpBar_Base.png");
		_hpBarBase[i]->SetTexture(hpBarBaseQuad);

		_hpBarGauge[i] = make_shared<Object>();
		auto hpBarGaugeQuad = make_shared<Quad>(L"Resource/Ui/HpBar/Enemy_HpBar_Gauge.png");
		_hpBarGauge[i]->SetTexture(hpBarGaugeQuad);

		_hpBarBase[i]->GetRender() = false;
		_hpBarGauge[i]->GetRender() = false;
	}

}
