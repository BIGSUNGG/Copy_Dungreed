#pragma once
class UI_EnemyHpBar : public UI
{
public:
	UI_EnemyHpBar();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Refresh() override;

protected:
	vector<shared_ptr<Object>> _hpBarBase;
	vector<shared_ptr<Object>> _hpBarGauge;

};

