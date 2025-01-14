#include "framework.h"
#include "UI_EnemyHpBar.h"

UI_EnemyHpBar::UI_EnemyHpBar()
	: UI()
{
}

void UI_EnemyHpBar::Update()
{
	auto& creatures = MAP_MANAGER->GetCurMap()->GetObjects()[Object::CREATURE];
	for (int i = 0; i < _hpBarBase.size(); i++)
	{
		if (creatures[i] != nullptr && creatures[i]->IsRender()) // 캐릭터가 렌더링되고 있다면
		{
			// 현재 HP 비율 구하기
			auto creature = dynamic_pointer_cast<Creature>(creatures[i]);
			float hpRatio = 0.0f;
			hpRatio = creature->GetStatus().GetHpRatio();
			
			// 적 캐릭터가 데미지를 받은 상태라면 Hp바 설정
			if (creature->GetCreatureType() == Creature::ENEMY && hpRatio < 1.0f) 
			{
				_hpBarBase[i]->SetIsRender(true);
				_hpBarGauge[i]->SetIsRender(true);

				_hpBarBase[i]->GetObjectTexture()->SetTop(creature->GetCollider()->Bottom() - CAMERA->GetPos().y - 10.0f);
				_hpBarBase[i]->GetPos().x = creature->GetPos().x - CAMERA->GetPos().x;

				_hpBarGauge[i]->GetPos() = _hpBarBase[i]->GetPos();

				_hpBarGauge[i]->GetObjectTexture()->GetTransform()->GetScale().x = hpRatio;
				_hpBarGauge[i]->GetObjectTexture()->SetLeft(_hpBarGauge[i]->GetPos().x - _hpBarGauge[i]->GetObjectTexture()->GetHalfSize().x);				
			}
			// 적 캐릭터가 아니거나 데미지를 입지않은 상태라면 Hp바 비활성화
			else
			{
				_hpBarBase[i]->SetIsRender(false);
				_hpBarGauge[i]->SetIsRender(false);
			}
		}
		else
		{
			_hpBarBase[i]->SetIsRender(false);
			_hpBarGauge[i]->SetIsRender(false);
		}
		
		_hpBarBase[i]->Update();
		_hpBarGauge[i]->Update();
	}
}

void UI_EnemyHpBar::Render()
{
	for (int i = 0; i < _hpBarBase.size(); i++)
		_hpBarBase[i]->Render();

	for (int i = 0; i < _hpBarGauge.size(); i++)
		_hpBarGauge[i]->Render();
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

		_hpBarBase[i]->SetIsRender(false);
		_hpBarGauge[i]->SetIsRender(false);
	}

}
