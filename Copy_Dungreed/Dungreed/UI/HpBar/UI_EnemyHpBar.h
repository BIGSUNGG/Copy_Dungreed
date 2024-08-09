#pragma once
class UI_EnemyHpBar : public UI
{
public:
	UI_EnemyHpBar();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Refresh() override;

protected:
	vector<shared_ptr<Object>> _hpBarBase; // HP바 베이스
	vector<shared_ptr<Object>> _hpBarGauge; // 현재 HP를 보여주는 게이지

};

