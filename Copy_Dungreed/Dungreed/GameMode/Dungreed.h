#pragma once
class Dungreed : public GameMode
{
public:
	Dungreed();

	// GameMode을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ImGuiRender() override;
private:
	shared_ptr<Map> _map;
};

