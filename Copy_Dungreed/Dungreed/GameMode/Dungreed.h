#pragma once
class Dungreed : public GameMode
{
public:
	Dungreed();

	// GameMode��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ImGuiRender() override;
private:
	shared_ptr<Map> _map;
};

